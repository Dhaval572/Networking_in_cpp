cmake_minimum_required(VERSION 3.25)

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
            -Werror
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