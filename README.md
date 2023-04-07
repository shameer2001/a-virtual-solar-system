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

### Command Line Interface

Here is an example and its output:

```
./build/solarSystemSimulator -t 0.001 -s 6.28
```

```
The initial position of Sun is (0, 0, 0).
The initial position of Mercury is (-0.362857, -0.168329, 0).
The initial position of Venus is (-0.635, -0.294576, 0).
The initial position of Earth is (-0.907143, -0.420823, 0).
The initial position of Mars is (-1.36071, -0.631235, 0).
The initial position of Jupiter is (-4.71714, -2.18828, 0).
The initial position of Saturn is (-8.61786, -3.99782, 0).
The initial position of Uranus is (-17.4171, -8.07981, 0).
The initial position of Neptune is (-27.305, -12.6668, 0).

The final position of Sun is (-0.000609735, -0.000468373, 0).
The final position of Mercury is (0.422259, 0.1975, 0).
The final position of Venus is (0.0746785, 0.72202, 0).
The final position of Earth is (-0.941993, -0.373222, 0).
The final position of Mars is (1.14375, 0.977918, 0).
The final position of Jupiter is (-2.9643, -4.27277, 0).
The final position of Saturn is (-7.56787, -5.74108, 0).
The final position of Uranus is (-16.7655, -9.35697, 0).
The final position of Neptune is (-26.8033, -13.6964, 0).
```
<br/>


## Energy of the System

### For all timesteps:

The initial total kinetic energy of the system is 0.000112389 \
The initial total potential energy of the system is -0.00022485 \
The initial total energy of the system is -0.000112461 

### For `dt = 0.0001` and total simulation time being 100 years:

The final total kinetic energy of the system is 0.000112392 \
The final total potential energy of the system is -0.000224841 \
The final total energy of the system is -0.000112448 

### For `dt = 0.001` and total simulation time being 100 years:

The final total kinetic energy of the system is 0.000112293 \
The final total potential energy of the system is -0.000224637 \
The final total energy of the system is -0.000112344 

### For `dt = 0.01` and total simulation time being 100 years:

The final total kinetic energy of the system is 0.000111844 \
The final total potential energy of the system is -0.000223577 \
The final total energy of the system is -0.000111733 

### For `dt = 0.1` and total simulation time being 100 years:

The final total kinetic energy of the system is 0.000110271 \
The final total potential energy of the system is -0.000219878 \
The final total energy of the system is -0.000109607 

### For `dt = 1.0` and total simulation time being 100 years:

The final total kinetic energy of the system is 0.000124885 \
The final total potential energy of the system is -0.000213331 \
The final total energy of the system is -8.84461e-05 

### For `dt = 62.8` and total simulation time being 100 years:

The final total kinetic energy of the system is 0.0416974 \
The final total potential energy of the system is -5.03234e-05 \
The final total energy of the system is 0.0416471 

### For `dt = 100.0` and total simulation time being 100 years:

The final total kinetic energy of the system is 0.105555 \
The final total potential energy of the system is -3.30823e-05 \
The final total energy of the system is 0.105522 

### For `dt = 314.0` and total simulation time being 100 years:

The final total kinetic energy of the system is 1.03974 \
The final total potential energy of the system is -1.11343e-05 \
The final total energy of the system is 1.03973 


<br/>

## Runtime of the Simulation

### With the Second Level Optimisation Flag:

#### For `dt = 0.0001` and total simulation time being 100 years:
The runtime of this simulation is 258.334 ms

#### For `dt = 0.001` and total simulation time being 100 years:
The runtime of this simulation is 24.4332 ms

#### For `dt = 0.01` and total simulation time being 100 years:
The runtime of this simulation is 2.22319 ms

#### For `dt = 0.1` and total simulation time being 100 years:
The runtime of this simulation is 0.223068 ms

#### For `dt = 1.0` and total simulation time being 100 years:
The runtime of this simulation is 0.036412 ms

#### For `dt = 62.8` and total simulation time being 100 years:
The runtime of this simulation is 0.016413 ms

#### For `dt = 100.0` and total simulation time being 100 years:
The runtime of this simulation is 0.016239 ms

#### For `dt = 314.0` and total simulation time being 100 years:
The runtime of this simulation is 0.016247 ms

#### The total simulation time is: 285.299 ms
#### The average simulation time is: 31.6999 ms

<br/>

### With No Optimisation Flag:

#### For `dt = 0.01` and total simulation time being 100 years:
The runtime of this simulation is 4.99966 ms


### With vs Without Optimisation Flag:

Comparing the runtime with `dt = 0.01` with and without the second level optimisation flag, we can see that with the optimisation flag the runtime is more than half that when with no optimisation flag. Therefore the second level optimisation flag `-O2` is effective and should be used in this simulation.

<br/><br/>


## Credits

This project is maintained by Dr. Jamie Quinn as part of UCL ARC's course, Research Computing in C++.
