#include "particle.hpp"

Particle::Particle(double in_mass) :
    mass{in_mass}
    {}
Particle::Particle(double in_mass, Eigen::Vector3d &in_pos, Eigen::Vector3d &in_vel, Eigen::Vector3d &in_acc) :
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


void Particle::update(double dt) {
    position += dt * velocity;
    velocity += dt * acceleration;
}