add_executable(solarSystemSimulator main.cpp)
target_compile_features(solarSystemSimulator PUBLIC cxx_std_17)
target_include_directories(solarSystemSimulator PUBLIC ../include)

# Optimisation flag
target_compile_options(solarSystemSimulator PRIVATE -O2)


find_package(Eigen3 3.4 REQUIRED)
find_package(OpenMP REQUIRED)

target_link_libraries(solarSystemSimulator PUBLIC Eigen3::Eigen OpenMP::OpenMP_CXX nbody_lib)