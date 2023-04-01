#include "particle.hpp"


Particle::Particle(double in_mass, Eigen::Vector3d& in_pos, Eigen::Vector3d& in_vel, Eigen::Vector3d& in_acc) :
    mass{in_mass}, position{in_pos}, velocity{in_vel}, acceleration{in_acc}
    {}  


double Particle::getMass() const {
    return mass;
}
Eigen::Vector3d Particle::getPosition() const {
    return position;
}
Eigen::Vector3d Particle::getVelocity() const {
    return velocity;
}
Eigen::Vector3d Particle::getAcceleration() const {
    return acceleration;
}



void Particle::updateAcceleration(Eigen::Vector3d& acc) {
    acceleration = acc;
}

void Particle::update(double dt) {
    position += dt * velocity;
    velocity += dt * acceleration;
}





// Acceleration felt by particle j due to particle i
Eigen::Vector3d calcAcceleration(const Particle& particle_i, const Particle& particle_j, double epsilon) {
    
    Eigen::Vector3d d_ji = (particle_i.getPosition() - particle_j.getPosition()).cwiseAbs(); // Distance between particles i & j

    double denominator = pow(d_ji.squaredNorm()   +   epsilon * epsilon,    3.0/2.0);
    Eigen::Vector3d numerator = particle_j.getPosition() - particle_i.getPosition(); // Distance between particles j and i

    return particle_j.getMass() * (numerator/denominator);
}






// Define == for 2 Particle class instances
bool operator==(const Particle& p1, const Particle& p2) {

    // If the mass, position, velocity and acceleration are all equal between the 2:
    if (
        (  p1.getMass() == p2.getMass() ) && 
        (  p1.getPosition() == p2.getPosition()  ) &&
        (  p1.getVelocity() == p2.getVelocity() ) &&
        (  p1.getAcceleration() == p2.getAcceleration() )  
        ) {
            return true;
    }
    else {
        return false;
    } 
}

// Add accelerations felt by a particle (particle_main)
void sumAccelerations(const std::vector<std::shared_ptr<Particle>>& particles,  Particle& particle_main) {
    Eigen::Vector3d acc_tot(0, 0, 0); 

    for (const auto& p : particles) {
        if ( !(*p == particle_main)) // If the particle in the list is not the particle who's acceleration is being calculated
        {
            acc_tot += calcAcceleration(particle_main, *p);
        }
    }
    particle_main.updateAcceleration(acc_tot);
}