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
Our solar system and a random solar system can be simulated using the solarSystemSimulator app. The guidance of the arguments for this application can be obtained using:
```
./build/solarSystemSimulator -h
```
The help argument can also be typed as ```--help```.


### Solar System Command Line Interface
There are two arguments that are needed to run the simulation:
```
./build/solarSystemSimulator -ss -t <timestep size> -s <simulation time>
```
The `ss` argument can also be typed as `--solar_system`. The timestep argument can also be typed as ```--timestep```. The total simulation time argument can also be typed as ```--simulation_time```. You can also adjust the softening factor in the calculations using `-e` or `-epsilon`.



### Random System Command Line Interface

There are three arguments that are needed to run the simulation:
```
./build/solarSystemSimulator -rs -n <number of bodies> -t <timestep size> -s <simulation time>
```
The `-rs` argument can also be typed as `--random_system`. The number argument can also be typed as `--number`. You can also adjust the softening factor in the calculations using `-e` or `-epsilon`. The timestep and total simulation time arguments are the same as the solar system app.



### Example

Here is an example and its output:
```
./build/solarSystemSimulator -ss -t 0.001 -s 2pi
```

```
The initial position of Sun is (0, 0, 0).
The initial position of Mercury is (0.398603, -0.0334015, 0).
The initial position of Venus is (0.660511, 0.231788, 0).
The initial position of Earth is (-0.0773197, -0.997006, 0).
The initial position of Mars is (1.49851, -0.0669091, 0).
The initial position of Jupiter is (-4.76597, 2.07978, 0).
The initial position of Saturn is (2.82026, -9.07172, 0).
The initial position of Uranus is (19.1975, 0.312663, 0).
The initial position of Neptune is (26.9617, -13.3819, 0).

The final position of Sun is (-0.000630235, 0.000124112, 0).
The final position of Mercury is (-0.466058, 0.0375412, 0).
The final position of Venus is (-0.145615, -0.711716, 0).
The final position of Earth is (-0.13688, -1.00319, 0).
The final position of Mars is (-1.46727, -0.340779, 0).
The final position of Jupiter is (-5.16362, -0.614664, 0).
The final position of Saturn is (4.68749, -8.26294, 0).
The final position of Uranus is (19.1206, 1.74438, 0).
The final position of Neptune is (27.4513, -12.3465, 0).
```
Note: Yes, you can use `pi` in the argument to represent the constant.

<br/><br/>


## Energy of the System

### For all timesteps:

The initial total kinetic energy of the system is 0.000112389 \
The initial total potential energy of the system is -0.000224804 \
The initial total energy of the system is -0.000112415

### For `dt = 0.0001` and total simulation time being 100 years:

The final total kinetic energy of the system is 0.000111994 \
The final total potential energy of the system is -0.000223687 \
The final total energy of the system is -0.000111693

### For `dt = 0.001` and total simulation time being 100 years:

The final total kinetic energy of the system is 0.000110185 \
The final total potential energy of the system is -0.000219996 \
The final total energy of the system is -0.000109811

### For `dt = 0.01` and total simulation time being 100 years:

The final total kinetic energy of the system is 0.000102216 \
The final total potential energy of the system is -0.000204711 \
The final total energy of the system is -0.000102495

### For `dt = 0.1` and total simulation time being 100 years:

The final total kinetic energy of the system is 7.27869e-05 \
The final total potential energy of the system is -0.000147695 \
The final total energy of the system is -7.49076e-05

### For `dt = 1.0` and total simulation time being 100 years:

The final total kinetic energy of the system is 4.0166e-05 \
The final total potential energy of the system is -6.71251e-05 \
The final total energy of the system is -2.69591e-05

### For `dt = 62.8` and total simulation time being 100 years:

The final total kinetic energy of the system is 0.0416869 \
The final total potential energy of the system is -2.17321e-06 \
The final total energy of the system is 0.0416848

### For `dt = 100.0` and total simulation time being 100 years:

The final total kinetic energy of the system is 0.105555 \
The final total potential energy of the system is -1.57413e-06 \
The final total energy of the system is 0.105553

### For `dt = 314.0` and total simulation time being 100 years:

The final total kinetic energy of the system is 1.03978 \
The final total potential energy of the system is -5.50335e-07 \
The final total energy of the system is 1.03978

### Comment:
The energy increases as the timestep size increases. In other words, the simulation gets less accurate as the larger timestep size.

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

#### Comment:
The total time decreases as the timestep size increases. The average time per timestep remains relatively constant.

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
The final total energy of the system is 0.0644139 

The total simulation time is: 19028.7 ms \
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

### Comment:
Both the accuracy (because the total energy increases away from 0) and speed get worse as the number of bodies increases.

<br/><br/>



## Parallelising with OpenMP

### Parallelising the `evolutionOfSystem()` function:

For a system of 2048 particles, a timestep of 0.01 and a total simulation time of 1 year. Parallelised the two small for loops in the function.

Before:
```
The total simulation time is: 137304 ms
The average time per timestep is: 218.289 ms
```

After:
```
The total simulation time is: 69346.5 ms
The average time per timestep is: 110.249 ms
```

The speed is nearly double. Other places to parallelise were considered such as the for loop in the `generateInitialConditions()` method of the `RandomSystem` class and the for loop in the `sumAccelerations()` function, however these cases increased overhead, did not lead to any improvement in speed and often gave errors when trying to run the app.


### The `collapse` vs `schedule` clauses:

The `collapse` clause was not used since there are no nested for loops present in the code for the simulation itself. The `schedule` clause was experimented with and no improvement in the performance was observed. When using `#pragma omp for schedule(dynamic)` in the `evolutionOfSystem()` function, the performance remained the same. When using, `#pragma omp for schedule(static)`, the performance worsened with about 40-50% greater total simulation and average per timestep times. When using, `#pragma omp for schedule(guided)` worsened the performance with about 50-60% greater total simulation and average per timestep times. Therefore, `schedule` was not used when parallelising.

<br/>

### Strong Scaling Experiment:
Note: Both scaling experiments use the second level optimisation flag `-O2`. 

Used a 2048 particle system, a timestep of 0.01 and a total simulation time of 1 year. My computer has only 2 physical cores. Below is a table of the strong scaling experiment conducted. The speedup is as a factor of the single-thread runtime to 3 decimal places.

| `OMP_NUM_THREADS | Time (ms) |  Speedup  |
|------------------|-----------|-----------|
|         1        |  125,519  |   1.000   |
|         2        |  71,479.6 |   0.569   |
|         4        |  68,428.4 |   0.545   |

Comment: The Speed is nearly doubled when using 2 threads which is what is expected. However, using 4 threads there is not much improvement rom 2 threads since the machine has only 2 physical cores. Therefore, a maximum of 2 threads gives the best performance.

<br/>

### Weak Scaling Experiment:
Below is a summary of the weak scaling experiment. The same timestep of 0.01 and simulation time of 1 year was used in each case.

| `OMP_NUM_THREADS | Num Particles | Time (ms) | Speedup |
|---|---|---|---|
| 1 | 2048 | 124,810 | 1.000 |
| 2 | 4096 | 308,618 | 2.473 |
| 4 | 8192 | 1,136,450 | 9.105 |

Comment: It is clear that using 2 threads and scaling the number of particles to the same proportion decreases the speed. However, the speedup is more than double that when using 1 thread. It can also be seen that the speedup when using 4 cores is 9 times. This is clearly not proportional to the thread number. This is because performance scales with the square of the number of particles. When using 4 threads, the substantial increase in speedup can also be explained by the fact that the cores of the machine are only 2 and exceeding the number of cores with the number of threads will lead to a much worse speed.

<br/><br/>

## Credits

This project is maintained by Dr. Jamie Quinn as part of UCL ARC's course, Research Computing in C++.
