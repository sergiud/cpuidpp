# CPUIDpp

![Linux](https://github.com/sergiud/cpuidpp/actions/workflows/linux.yml/badge.svg)
![macOS](https://github.com/sergiud/cpuidpp/actions/workflows/macos.yml/badge.svg)
![Windows](https://github.com/sergiud/cpuidpp/actions/workflows/windows.yml/badge.svg)
[![codecov](https://codecov.io/gh/sergiud/cpuidpp/branch/master/graph/badge.svg?token=7TS1PO9WDD)](https://codecov.io/gh/sergiud/cpuidpp)

This repository provides a C++11 library for identifying CPU features.

## Requirements

* C++11 compiler
* CMake 3.16
* Doxygen (optional)

## Getting Started

To compile, run:

```bash
cmake -S . -B build/
cmake --build build/
```
Afterwards, the test application `test_cpuidpp` can be run in the `build`
directory.
