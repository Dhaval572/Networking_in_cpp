# Networking in C++

Network programming with Standalone Asio.

## Prerequisites

- **Git**
- **CMake** >= 3.25
- **Ninja**
- **C++ Compiler** (GCC/Clang on Linux/Mac, MSVC on Windows)

## Quick Start

```bash
git clone <repo-url> && cd Networking_in_cpp
cmake --preset debug
ninja -C build
./build/main
```

vcpkg is installed automatically on first run if not found.

## Presets

| Preset | Command | Description |
|--------|---------|-------------|
| `debug` | `cmake --preset debug` | Debug build with symbols |
| `release` | `cmake --preset release` | Optimized release build |

## Dependencies

Managed via vcpkg (`vcpkg.json`):

- [Asio](https://think-async.com/Asio/) - Standalone network I/O
- [Google Benchmark](https://github.com/google/benchmark) - Microbenchmark framework

## Project Structure

```
.
├── src/main.cpp                 # Main application
├── benchmarks/benchmark_main.cpp
├── CMakeLists.txt               # Build config + vcpkg auto-bootstrap
├── CMakePresets.json            # Build presets
├── vcpkg.json                   # Dependencies manifest
└── .clang-format                # Code style
```

## Platform Support

| OS | vcpkg Location | Status |
|----|---------------|--------|
| Linux | `~/vcpkg` | Supported |
| macOS | `~/vcpkg` | Supported |
| Windows | `C:/vcpkg` | Supported |
