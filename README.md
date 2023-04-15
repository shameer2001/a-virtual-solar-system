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
<br/><br/>


## Energy of the System

### For all timesteps:

The initial total kinetic energy of the system is 0.000112389 \
The initial total potential energy of the system is -0.00022485 \
The initial total energy of the system is -0.000112461 

### For `dt = 0.0001` and total simulation time being 100 years:

The final total kinetic energy of the system is 0.000112537 \
The final total potential energy of the system is -0.000224276 \
The final total energy of the system is -0.000111739

### For `dt = 0.001` and total simulation time being 100 years:

The final total kinetic energy of the system is 0.000110598 \
The final total potential energy of the system is -0.000220453 \
The final total energy of the system is -0.000109855

### For `dt = 0.01` and total simulation time being 100 years:

The final total kinetic energy of the system is 0.000102691 \
The final total potential energy of the system is -0.000205216 \
The final total energy of the system is -0.000102525

### For `dt = 0.1` and total simulation time being 100 years:

The final total kinetic energy of the system is 7.43482e-05 \
The final total potential energy of the system is -0.000149266 \
The final total energy of the system is -7.4918e-05

### For `dt = 1.0` and total simulation time being 100 years:

The final total kinetic energy of the system is 4.25877e-05 \
The final total potential energy of the system is -6.97032e-05 \
The final total energy of the system is -2.71155e-05

### For `dt = 62.8` and total simulation time being 100 years:

The final total kinetic energy of the system is 0.041685 \
The final total potential energy of the system is -2.15063e-06 \
The final total energy of the system is 0.0416828

### For `dt = 100.0` and total simulation time being 100 years:

The final total kinetic energy of the system is 0.10555 \
The final total potential energy of the system is -1.54533e-06 \
The final total energy of the system is 0.105548

### For `dt = 314.0` and total simulation time being 100 years:

The final total kinetic energy of the system is 1.03974 \
The final total potential energy of the system is -5.37401e-07 \
The final total energy of the system is 1.03974


<br/><br/>

## Runtime of the Simulation
Note: The initial and final energies for each timestep are the same as the corresponding timesteps above.

### With the Second Level Optimisation Flag:

#### For `dt = 0.0001` and total simulation time being 100 years:
The total simulation time is: 29559.6 ms \
The average time per timestep is: 0.00470455 ms 

#### For `dt = 0.001` and total simulation time being 100 years:
The total simulation time is: 2215.19 ms \
The average time per timestep is: 0.00352558 ms

#### For `dt = 0.01` and total simulation time being 100 years:
The total simulation time is: 233.723 ms \
The average time per timestep is: 0.0037198 ms

#### For `dt = 0.1` and total simulation time being 100 years:
The total simulation time is: 33.5678 ms \
The average time per timestep is: 0.00534179 ms

#### For `dt = 1.0` and total simulation time being 100 years:
The total simulation time is: 2.55285 ms \
The average time per timestep is: 0.00405858 ms

#### For `dt = 62.8` and total simulation time being 100 years:
The total simulation time is: 0.074653 ms \
The average time per timestep is: 0.00678664 ms

#### For `dt = 100.0` and total simulation time being 100 years:
The total simulation time is: 0.061043 ms \
The average time per timestep is: 0.00872043 ms

#### For `dt = 314.0` and total simulation time being 100 years:
The total simulation time is: 0.043621 ms \
The average time per timestep is: 0.0145403 ms


<br/>

### With No Optimisation Flag:

#### For `dt = 0.01` and total simulation time being 100 years:
The total simulation time is: 238.047 ms
The average time per timestep is: 0.00378862 ms


### With vs Without Optimisation Flag:

Comparing the runtime with `dt = 0.01` with and without the second level optimisation flag, we can see that with the optimisation flag the runtime is virtually identical to that when with no optimisation flag. Therefore the second level optimisation flag `-O2` is not very effective here and is not of much benefit. 

### Best timestep:

The best timestep is one that balances performance/speed and accuracy. Looking at the total energy and simulation time, it sees that a timestep of 0.01 seems to be the best since the time is well below 1 millisecond and the final total energy is the same order of magnitude as the initial.

<br/><br/>



## Random System Generator Performance

### For 8 particles, `dt = 0.01` and total simulation time being 1/2 year:


The initial total kinetic energy of the system is 0.000150334 \
The initial total potential energy of the system is -0.000301027 \
The initial total energy of the system is -0.000150693 

The final total kinetic energy of the system is 0.000150346 \
The final total potential energy of the system is -0.000301025 \
The final total energy of the system is -0.00015068

The total simulation time is: 1.19732 ms \
The average time per timestep is: 0.00380101 ms

### For 64 particles, `dt = 0.01` and total simulation time being 1/2 year:


The initial total kinetic energy of the system is 0.00234098 \
The initial total potential energy of the system is -0.00471449 \
The initial total energy of the system is -0.00237352

The final total kinetic energy of the system is 0.00214679 \
The final total potential energy of the system is -0.00433541 \
The final total energy of the system is -0.00218862

The total simulation time is: 71.4689 ms \
The average time per timestep is: 0.226885 ms

### For 256 particles, `dt = 0.01` and total simulation time being 1/2 year:


The initial total kinetic energy of the system is 0.00895117 \
The initial total potential energy of the system is -0.0184524 \
The initial total energy of the system is -0.00950119

The final total kinetic energy of the system is 0.0100518 \
The final total potential energy of the system is -0.0174344 \
The final total energy of the system is -0.00738262

The total simulation time is: 1171.37 ms \
The average time per timestep is: 3.71864 ms

### For 1024 particles, `dt = 0.01` and total simulation time being 1/2 year:


The initial total kinetic energy of the system is 0.0393058 \
The initial total potential energy of the system is -0.0884766 \
The initial total energy of the system is -0.0491708

The final total kinetic energy of the system is 0.146506 \
The final total potential energy of the system is -0.0820921 \
The final total energy of the system is 0.0644139 \

The total simulation time is: 19028.7 ms
The average time per timestep is: 60.4085 ms

### For 2048 particles, `dt = 0.01` and total simulation time being 1/2 year:


The initial total kinetic energy of the system is 0.0747521 \
The initial total potential energy of the system is -0.18705 \
The initial total energy of the system is -0.112298

The final total kinetic energy of the system is 7.64706 \
The final total potential energy of the system is -0.174878 \
The final total energy of the system is 7.47219

The total simulation time is: 64210.6 ms \
The average time per timestep is: 203.843 ms

### Note:
Both the accuracy (because the total energy increases away from 0) and speed get worse as the number of bodies increases.

<br/><br/>

## Credits

This project is maintained by Dr. Jamie Quinn as part of UCL ARC's course, Research Computing in C++.
