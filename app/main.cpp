#include "particle.hpp"
#include "solarSystem.hpp"
#include "randomParticleSystem.hpp"


void help() {
  std::cout << "Usage: solarSystemSimulator [options]\n"
            << " \n"
            << "Options:\n"
            << "  -ss,  --solar_system       Select to simulate our solar system.\n"
            << "  -rs,  --random_system      Select to simulate a random solar system with random bodies.\n"
            << "  -n,   --number             Set the number of bodies in the random system (must select random system first). Type is integer.\n"
            << "  -e,   --epsilon            Set the softening factor for the random system. Type is double. Default is 0.0.\n"
            << "  -t,   --timestep           Set the timestep of the simulation. Type is double.\n"
            << "  -s,   --simulation_time    Set the total simulation time. Type is double.\n"
            << "  -h,   --help               Show this help message.\n"
            << " \n"
            << "Note 1 : The units for the time arguments are in radians where 2π represents one full earth cycle (i.e. one year).\n"
            << "Note 2 : You can use 'pi' in the simulation time argument to input a precise value of π and multiply it with any number BEFORE 'pi'\n"
            << "         E.G. 2pi = 2π\n"          
            << " "
            << std::endl;
}



int main(int argc, char *argv[]) 
{
  // Parse command line arguments
  bool solarsystem = false;
  bool randomsystem = false;
  int num_bodies = 0;
  double soft_fac = 0.0; // The softening factor i.e epsilon
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

    if (arg == "-ss" || arg == "--solar_system") {
      solarsystem = true;
    }
    else if (arg == "-rs" || arg == "--random_system") {
      randomsystem = true;
    }




    else if (arg == "-n" || arg == "--number") {
      if (i + 1 < argc) // If there is a value after this argument
      {
        std::string num_arg = argv[i + 1];
        for (auto c : num_arg) { // Loop through each char in the string
          if (c != '-' && !std::isdigit(c)) { // Check that there is no positive non-integer character
            help();
            throw std::invalid_argument("Number argument must be an integer");
          }
        }

        num_bodies = std::stoi(num_arg); 
        i++;
      }
      else 
      {
        help();
        throw std::invalid_argument("No value given for number argument.");
        return 1;
      }
      // Ensure random system is selected for this input to be used:
      if (randomsystem != true) {
        help();
        throw std::invalid_argument("Random system must be selected first to use number argument.");
        return 1;
      }
    }

    else if (arg == "-e" || arg == "--epsilon")
    {
      if (i + 1 < argc)
      {
        const char* input = argv[i + 1];
        char* endptr;
        soft_fac = strtod(input, &endptr); // Convert char to double using strtod()

        if (*endptr != '\0') { // If non-numerical character in argument
          help();
          throw std::invalid_argument("Invalid character encountered in softening factor argument.");
        }
        i++;
      }
      else 
      {
        help();
        throw std::invalid_argument("No value given for epsilon argument.");
        return 1;
      }
    }

    else if (arg == "-t" || arg == "--timestep")
    {
      if (i + 1 < argc)
      {
        const char* input = argv[i + 1];
        char* endptr;
        dt = strtod(input, &endptr); // Convert timestep to double

        if (*endptr != '\0') { // If non-numerical character in argument
          help();
          throw std::invalid_argument("Invalid character encountered in timestep argument.");
        }
        i++;
      }
      else 
      {
        help();
        throw std::invalid_argument("No value given for timestep argument.");
        return 1;
      }
    }

    else if (arg == "-s" || arg == "--simulation_time")
    {
      if (i + 1 < argc) 
      {
        std::string sim_time_str(argv[i + 1]); // Convert the input to string
        size_t pi_pos = sim_time_str.find("pi"); // Find position of "pi"

        // If no "pi" found in argument
        if (pi_pos == std::string::npos) { 
          const char* input = argv[i + 1];
          char* endptr;
          sim_time = strtod(input, &endptr); // Simulation time as input if input is a double

          if (*endptr != '\0') { // If non-numerical character in argument
            help();
            throw std::invalid_argument("The only non-numerical characters allowed are 'pi'.");
          }
        }  

        else {
          std::string x_str = sim_time_str.substr(0, pi_pos); // String between position 0 and pi_pos (ie any "coefficient" of pi)

          if (sim_time_str.length() - 2 !=  pi_pos) { // If characters/numbers after pi
            help();
            throw std::invalid_argument("The only non-numerical characters allowed are 'pi' and it must be at the end.");
          }
          else if (x_str == "") { // If no coefficient
            sim_time = M_PI;
          }
          else {
            double x = std::stod(x_str);
            sim_time = x * M_PI;
          }
        }
        i++;
      }


      else 
      {
        help();
        throw std::invalid_argument("No value given for simulation time argument.");
        return 1;
      }
    }




    else if (arg == "-h" || arg == "--help")
    {
      help();
      return 0;
    }

  }


  // If neither system is selected
  if (solarsystem == false && randomsystem == false) {
    help();
    throw std::invalid_argument("Did not select any system."); 
    return 1;
  }
  // If both systems are selected
  else if (solarsystem == true && randomsystem == true) {
    help();
    throw std::invalid_argument("Both systems cannot be simulated at the same time."); 
    return 1;
  }













  // Use pointer to base class generateInitialConditions method instead of calling from subclasses
  // This will reduce code duplication and reduce memory usage
  InitialConditionGenerator* systems[2]; // Pointer to initial condition generator base class


  if (solarsystem == true) {

    systems[0] = new SolarSystem(); // Create object of SolarSystem class
    SolarSystem* solar_system = dynamic_cast<SolarSystem*>(systems[0]); // Cast the already defined InitialConditionGenerator Pointer to a SolarSystem pointer. 
    // i.e. you can use solar_system as a pointer to SolarSystem and use the other methods exclusive to the SolarSystem class

    try {
      systems[0]->generateInitialConditions();
      solar_system->printMessages(); 
      printEnergyMessages(solar_system->getCelestialBodyList());


      auto start_time = std::chrono::high_resolution_clock::now();
      systems[0]->generateInitialConditions(); // Run this again to measure total simulation time
      evolutionOfSystem(solar_system->getCelestialBodyList(), dt, sim_time, soft_fac); // Run simulation evolution 
      auto end_time = std::chrono::high_resolution_clock::now();


      solar_system->printMessages();
      printEnergyMessages(solar_system->getCelestialBodyList());


      int num_timesteps = std::ceil( sim_time / dt ); // Number of timesteps needed in simulation (round up to nearest int)
      double runtime = std::chrono::duration<double, std::milli>(end_time - start_time).count();
      std::cout << "The total simulation time is: " << runtime << " ms\n"
                << "The average time per timestep is: " << runtime/num_timesteps << " ms\n"         
      << std::endl;
    }

    catch(const std::exception &e) {
      help();
      std::cerr << "ERROR: " << e.what() << std::endl; // If dt and/or sim_time are negative
    }       

    

  }











  else if (randomsystem == true) {
    try 
    {
      systems[1] = new RandomSystem(num_bodies); // Create object of RandomSystem class
      RandomSystem* random_system = dynamic_cast<RandomSystem*>(systems[1]); // Cast the already defined InitialConditionGenerator Pointer to a RandomSystem pointer

      // Simulate random system and it's evolution:
      systems[1]->generateInitialConditions();
      printEnergyMessages(random_system->getCelestialBodyList()); 


      auto start_time = std::chrono::high_resolution_clock::now();
      systems[1]->generateInitialConditions();
      evolutionOfSystem(random_system->getCelestialBodyList(), dt, sim_time, soft_fac); // Run simulation evolution    
      auto end_time = std::chrono::high_resolution_clock::now();
      
      
      printEnergyMessages(random_system->getCelestialBodyList());  
      int num_timesteps = std::ceil( sim_time / dt ); 

      double runtime = std::chrono::duration<double, std::milli>(end_time - start_time).count();
      std::cout << "The total simulation time is: " << runtime << " ms\n"
                << "The average time per timestep is: " << runtime/num_timesteps << " ms\n"         
      << std::endl;

      // Print number of max threads
      int thread_num_max = omp_get_max_threads();
      std::cout << "Max threads: " << thread_num_max << "\n" << std::endl;


    }

    catch(const std::exception &e)
    {
      help();
      std::cerr << "ERROR: " << e.what() << std::endl; // If num_bodies and/or dt and/or total_time is negative 
    }

  }










    
  return 0;
}

