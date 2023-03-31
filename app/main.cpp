#include <iostream>
#include "particle.hpp"
#include "solarSystem.hpp"




void help() {
  std::cout << "Usage: solarSystemSimulator [options]\n"
            << "Options:\n"
            << "  -t, --timestep           Set the timestep in seconds.\n"
            << "  -s, --simulation-time    Set the total simulation time in seconds.\n"
            << "  -h, --help               Show this help message.\n";
}



int main(int argc, char *argv[]) 
{
  // Parse command line arguments
  bool dt = 0.0;
  bool sim_time = 0.0;

  for (int i = 1; i < argc; i++)
  {
    std::string arg = argv[i];

    if (arg == "-t" || arg == "--timestep")
    {
      if (i + 1 < argc) 
      {
        dt = argv[i + 1]; // Argument after --t is the timestep value
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
        sim_time = argv[i + 1]; // Argument after --t is the filename
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

  return 0;
}

