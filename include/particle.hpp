#ifndef particle_hpp
#define particle_hpp

#include <Eigen/Core>
#include <memory>

class Particle {
    public:
        Particle(double in_mass, Eigen::Vector3d& in_pos, Eigen::Vector3d& in_vel, Eigen::Vector3d& in_acc); 

        // get functions:
        Eigen::Vector3d getPosition() const;
        Eigen::Vector3d getVelocity() const;
        Eigen::Vector3d getAcceleration() const;
        double getMass() const;

        // Update functions:
        void updateAcceleration(Eigen::Vector3d& acc);
        void update(double dt);
        

        

    private:
        double mass;
        Eigen::Vector3d position;
        Eigen::Vector3d velocity;
        Eigen::Vector3d acceleration;
        

};


Eigen::Vector3d calcAcceleration(const Particle& particle1, const Particle& particle2, double elipson = 0.0);

bool operator==(const Particle& p1, const Particle& p2);
void sumAccelerations(const std::vector<std::shared_ptr<Particle>>& particles, Particle& particle_main); // The list is of shared pointers of Particles to save memory



#endif