#include <iostream>
#include "particle.hpp"
#include "solarSystem.hpp"



void help() {
  std::cout << "Usage: solarSystemSimulator [options]\n"
            << "Options:\n"
            << "  -t, --timestep           Set the timestep.\n"
            << "  -s, --simulation-time    Set the total simulation time.\n"
            << "  -h, --help               Show this help message.\n"
            << "Note: The units for the time arguments are in radians where 2pi represents one full earth cycle (i.e. one year).";
}



int main(int argc, char *argv[]) 
{
  // Parse command line arguments
  double dt = 0.0;
  double sim_time = 0.0;

  for (int i = 1; i < argc; i++)
  {
    std::string arg = argv[i];

    if (arg == "-t" || arg == "--timestep")
    {
      if (i + 1 < argc) // Argument after --t is the timestep value
      {
        dt = strtod(argv[i + 1], NULL); // Convert char to double
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


    else 
    {
      help();
      return 0;
    }

  }

  SolarSystem solar_system;
  solar_system.InitialConditionGenerator();
  solar_system.printMessages();
  solar_system.evolutionOfSolarSystem(dt, sim_time);
  solar_system.printMessages();




  return 0;
}

