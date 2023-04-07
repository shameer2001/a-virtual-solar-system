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

  auto start_time = std::chrono::high_resolution_clock::now();
  solar_system.InitialConditionGenerator();

  #ifdef DEBUG // Disable output when debug enabled in order to prevent inclusion in simulation time calculation
  solar_system.printMessages(); 
  
  std::cout << "The initial total kinetic energy of the system is " << solar_system.totalKineticEnergy() << "\n"
            << "The initial total potential energy of the system is " << solar_system.totalPotentialEnergy() << "\n"
            << "The initial total energy of the system is " << solar_system.totalEnergy() << "\n"
  << std::endl;
  #endif


  solar_system.evolutionOfSolarSystem(dt, sim_time); // Run evolution simulation
  auto end_time = std::chrono::high_resolution_clock::now();

  solar_system.printMessages();

  std::cout << "The final total kinetic energy of the system is " << solar_system.totalKineticEnergy() << "\n"
            << "The final total potential energy of the system is " << solar_system.totalPotentialEnergy() << "\n"
            << "The final total energy of the system is " << solar_system.totalEnergy() << "\n"
  << std::endl;

  std::cout << "The runtime of the simulation is " 
  << std::chrono::duration<double, std::milli>(end_time - start_time).count() 
  << " ms"
  << std::endl;

  return 0;
}

