cmake_minimum_required(VERSION 3.25)

# === vcpkg Auto-Bootstrap ===
# Step 1: Resolve VCPKG_ROOT - check env, then default locations, then bootstrap
if(NOT DEFINED ENV{VCPKG_ROOT} OR NOT EXISTS "$ENV{VCPKG_ROOT}/vcpkg")
  if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set(_VCPKG_DEFAULT "C:/vcpkg")
  else()
    set(_VCPKG_DEFAULT "$ENV{HOME}/vcpkg")
  endif()

  if(EXISTS "${_VCPKG_DEFAULT}/vcpkg")
    set(ENV{VCPKG_ROOT} "${_VCPKG_DEFAULT}")
    message(STATUS "Auto-detected vcpkg at ${_VCPKG_DEFAULT}")
  else()
    message(STATUS "vcpkg not found. Installing...")

    find_program(_GIT git REQUIRED)
    execute_process(
            COMMAND
                ${_GIT}
                clone
                https://github.com/microsoft/vcpkg.git
                "${_VCPKG_DEFAULT}"
        )

    if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
      execute_process(
                COMMAND
                    "${_VCPKG_DEFAULT}/bootstrap-vcpkg.bat"
                    -disableMetrics
            )
    else()
      execute_process(
                COMMAND
                    "${_VCPKG_DEFAULT}/bootstrap-vcpkg.sh"
                    -disableMetrics
            )
    endif()

    set(ENV{VCPKG_ROOT} "${_VCPKG_DEFAULT}")
    message(STATUS "vcpkg installed at ${_VCPKG_DEFAULT}")
  endif()
endif()

if(NOT CMAKE_TOOLCHAIN_FILE)
  set(
      CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
    )
endif()
# === End vcpkg Auto-Bootstrap ===

set(PROJECT_NAME main)

project(
    ${PROJECT_NAME}
    VERSION 1.0.0
    DESCRIPTION "Network programming with Standalone Asio"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(asio CONFIG REQUIRED)
find_package(benchmark CONFIG REQUIRED)

add_library(project_options INTERFACE)

target_compile_features(
    project_options
    INTERFACE
        cxx_std_20
)

add_library(project_warnings INTERFACE)

target_compile_options(
    project_warnings
    INTERFACE
        $<$<CXX_COMPILER_ID:GNU,Clang>:
            -Wall
            -Wextra
            -Wpedantic
            # -Werror # Not needed in learning face
        >
        $<$<CXX_COMPILER_ID:MSVC>:
            /W4
            /WX
        >
)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        project_options
        project_warnings
        asio::asio
)

target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
        ASIO_STANDALONE
)

add_executable(
    ${PROJECT_NAME}_benchmarks
    benchmarks/benchmark_main.cpp
)

target_link_libraries(
    ${PROJECT_NAME}_benchmarks
    PRIVATE
        project_options
        project_warnings
        benchmark::benchmark
)
