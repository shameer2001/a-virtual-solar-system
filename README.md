# A Virtual Solar System

This is the starting repository for assignment 2 of PHAS0100: Research Computing with C++. You may add or remove C++ files in any directory. You should organise the files as you see fit but do read the Folder Structure section below to understand the intended use of the existing folders.

## Installing dependencies

We are using the package manager Conan to install the dependencies Catch2 and Eigen. In order to use CMake's `Release` target for performance and `Debug` for debugging, the libraries must be installed twice with:

```
conan install . --output-folder=build --build=missing -s build_type=Debug
conan install . --output-folder=build --build=missing -s build_type=Release
```

If you delete the `build` directory to clean your build, you may have to install the dependencies again.

## Building

To build from the project root directory you should run:

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

If you wish to debug your code, you should replace `Release` with `Debug`. For performance measurements, ensure you have built with the `Release` target.

## Testing

Once the project has been built, it can be tested by running:

```
cd build
ctest
```

## Folder structure

The project is split into four main parts aligning with the folder structure described in [the relevant section in Modern CMake](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html):

- `app/` contains all code implementing the command-line application.
- `lib/` contains all non-app code. Only code in this directory can be accessed by the unit tests.
- `include/` contains all `.hpp` files.
- `test/` contains all unit tests.

You are expected to edit the `CMakeLists.txt` file in each folder to add or remove sources as necessary. For example, if you create a new file `test/particle_test.cpp`, you must add `particle_test.cpp` to the line `add_executable(tests test.cpp)` in `test/CMakeLists.txt`. Please ensure you are comfortable editing these files well before the submission deadline. If you feel you are struggling with the CMake files, please see the Getting Help section of the assignment instructions.

## Usage Instructions

### Command Line Intreface

Here is an example and its output:

```
./build/solarSystemSimulator -t 0.001 -s 6.28
```

```
The initial position of Sun is (0, 0, 0).

The initial position of Mercury is (0.23913, 0.320651, 0).

The initial position of Venus is (0.418477, 0.561139, 0).

The initial position of Earth is (0.597824, 0.801628, 0).

The initial position of Mars is (0.896736, 1.20244, 0).

The initial position of Jupiter is (3.10868, 4.16846, 0).

The initial position of Saturn is (5.67933, 7.61546, 0).

The initial position of Uranus is (11.4782, 15.3912, 0).

The initial position of Neptune is (17.9945, 24.129, 0).

The final position of Sun is (0.000313251, 0.000701112, 0).

The final position of Mercury is (-0.282147, -0.370992, 0).

The final position of Venus is (0.273363, -0.672404, 0).

The final position of Earth is (0.654158, 0.773766, 0).

The final position of Mars is (-0.544033, -1.40303, 0).

The final position of Jupiter is (0.577121, 5.16823, 0).

The final position of Saturn is (3.92777, 8.649, 0).

The final position of Uranus is (10.2983, 16.2043, 0).

The final position of Neptune is (17.0641, 24.7956, 0).
```
## Credits

This project is maintained by Dr. Jamie Quinn as part of UCL ARC's course, Research Computing in C++.
