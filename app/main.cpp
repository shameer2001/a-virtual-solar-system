#include <iostream>
#include "particle.hpp"
#include "solarSystem.hpp"
#include <chrono>



void help() {
  std::cout << "Usage: solarSystemSimulator [options]\n"
            << "Options:\n"
            << "  -t, --timestep           Set the timestep.\n"
            << "  -s, --simulation-time    Set the total simulation time.\n"
            << "  -h, --help               Show this help message.\n"
            << "Note: The units for the time arguments are in radians where 2π represents one full earth cycle (i.e. one year).";
}



int main(int argc, char *argv[]) 
{
  // Parse command line arguments
  double dt = 0.0;
  double sim_time = 0.0;

  if (argc == 1) // When there are no arguments given
  {
    help();
    return 1;
  }

  for (int i = 1; i < argc; i++)
  {
    std::string arg = argv[i];

    if (arg == "-t" || arg == "--timestep")
    {
      if (i + 1 < argc) // Argument after --t is the timestep value
      {
        dt = strtod(argv[i + 1], NULL); // Convert char to double using strtod()
        i++;
      }
      else 
      {
        help();
        return 1;
      }
    
    }


    else if (arg == "-s" || arg == "--simulation-time" && (i+1)<argc)
    {
      if (i + 1 < argc) 
      {
        sim_time = strtod(argv[i + 1], NULL); 
        i++;
      }
      else 
      {
        help();
        return 1;
      }
    }


    else if (arg == "-h" || arg == "--help")
    {
      help();
      return 0;
    }

  }

  // Simulate solar system and it's evolution
  SolarSystem solar_system;

  solar_system.generateInitialConditions();
  solar_system.printMessages(); 
  solar_system.printEnergyMessages();

  solar_system.evolutionOfSolarSystem(dt, sim_time); // Run evolution simulation
  solar_system.printMessages();
  solar_system.printEnergyMessages();



  // Run simulation for 1 year (2pi) and dt = 0.001:
  std::cout << "=======Running the simulation for one year and with a dt of 0.001=======\n" << std::endl;
  solar_system.generateInitialConditions();
  solar_system.printMessages();
  solar_system.evolutionOfSolarSystem(0.001, 2 * M_PI); 
  solar_system.printMessages();




  // Run simulation for 1 year (2pi) and 8 different timesteps and print energies:
  std::vector<double> dt_list{0.0001, 0.001, 0.01, 0.1, 1.0, 62.8, 100.0, 314.0};
  std::cout << "=======Run simulation for 1 year and 8 different timesteps and PRINT ENERGIES=======\n" << std::endl;

  for(double& dt: dt_list) {
    std::cout << "-------Running for one year and with dt = " << dt << "-------\n" << std::endl;

    solar_system.generateInitialConditions();
    solar_system.printMessages(); 
    solar_system.printEnergyMessages();

    solar_system.evolutionOfSolarSystem(dt, 2 * M_PI); 
    solar_system.printMessages();
    solar_system.printEnergyMessages();
  }




  // Run simulation for 1 year (2pi) and 8 different timesteps and print simulation time:
  double total_runtime = 0.0;
  std::cout << "=======Run simulation for 1 year and 8 different timesteps and PRINT SIMULATION TIME=======\n" << std::endl;
  
  for(double& dt: dt_list) {
    std::cout << "-------Running for one year and with dt = " << dt << " -------\n" <<std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();
    solar_system.generateInitialConditions();

    #ifdef DEBUG // Disable output when debug enabled in order to prevent inclusion in simulation time calculation
    solar_system.printMessages(); 
    solar_system.printEnergyMessages();
    #endif

    solar_system.evolutionOfSolarSystem(dt, 2 * M_PI); 
    auto end_time = std::chrono::high_resolution_clock::now();

    solar_system.printMessages();
    solar_system.printEnergyMessages();

    double runtime = std::chrono::duration<double, std::milli>(end_time - start_time).count();
    std::cout << "The runtime of this simulation is " 
              << runtime << " ms\n"
    << std::endl;

    total_runtime += runtime;
  }

  std::cout << "The total simulation time is: " << total_runtime << " ms\n"
            << "The average simulation time is: " << total_runtime / solar_system.getCelestialBodyList().size() << " ms\n"
  << std::endl;





  // Run simulation for 1 year (2pi) and dt = 0.01 and print simulation time (for 0 optimisation flags):
  std::cout << "=======Running for one year and with dt = 0.01=======\n" <<std::endl;

  auto start_time = std::chrono::high_resolution_clock::now();
  solar_system.generateInitialConditions();

  #ifdef DEBUG
  solar_system.printMessages(); 
  solar_system.printEnergyMessages();
  #endif

  solar_system.evolutionOfSolarSystem(0.01, 2 * M_PI); 
  auto end_time = std::chrono::high_resolution_clock::now();

  solar_system.printMessages();
  solar_system.printEnergyMessages();

  double runtime = std::chrono::duration<double, std::milli>(end_time - start_time).count();
  std::cout << "The runtime of this simulation is " 
            << runtime << " ms\n"
  << std::endl;




  return 0;
}

