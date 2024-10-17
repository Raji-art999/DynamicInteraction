// src/ParticleSystem.h
#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "Particle.h"
#include <vector>
#include <boost/thread.hpp>
#include <string>

class ParticleSystem {
private:
    std::vector<Particle> particles;
    boost::mutex particleMutex; // Mutex for thread safety

public:
    ParticleSystem(size_t numParticles);
    
    const std::vector<Particle>& getParticles() const;
    void updateParticles(float deltaTime);
    void saveToHDF5(const std::string& filename);
};

#endif // PARTICLESYSTEM_H
