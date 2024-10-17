// src/ParticleSystem.cpp
#include "ParticleSystem.h"
#include <random>
#include <H5Cpp.h> // Include HDF5 C++ API
#include <boost/thread.hpp> // Include Boost thread library

ParticleSystem::ParticleSystem(size_t numParticles) {
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

    for (size_t i = 0; i < numParticles; ++i) {
        float x = distribution(generator);
        float y = distribution(generator);
        float z = distribution(generator);
        float vx = distribution(generator) * 0.1f; // Velocity range
        float vy = distribution(generator) * 0.1f;
        float vz = distribution(generator) * 0.1f;

        particles.emplace_back(x, y, z, vx, vy, vz); // Create Particle objects
    }
}

const std::vector<Particle>& ParticleSystem::getParticles() const {
    return particles; // Return the particles vector
}

void ParticleSystem::updateParticles(float dt) {
    boost::thread_group threads; // Create a thread group

    for (size_t i = 0; i < particles.size(); ++i) {
        threads.create_thread([this, dt, i]() {
            // Lock to ensure thread safety when accessing shared data
            boost::mutex::scoped_lock lock(particleMutex);

            // Update position using setters
            particles[i].setX(particles[i].getX() + particles[i].getVx() * dt);
            particles[i].setY(particles[i].getY() + particles[i].getVy() * dt);
            particles[i].setZ(particles[i].getZ() + particles[i].getVz() * dt);
        });
    }

    threads.join_all(); // Wait for all threads to finish
}

void ParticleSystem::saveToHDF5(const std::string& filename) {
    H5::H5File file(filename, H5F_ACC_TRUNC); // Create a new HDF5 file
    hsize_t dims[2] = {particles.size(), 6}; // 6 for x, y, z, vx, vy, vz
    H5::DataSpace dataspace(2, dims);
    
    // Create dataset
    H5::DataSet dataset = file.createDataSet("particles", H5::PredType::NATIVE_FLOAT, dataspace);
    
    // Prepare data for writing
    std::vector<float> data(particles.size() * 6); // Flat vector to store particle data
    for (size_t i = 0; i < particles.size(); ++i) {
        data[i * 6] = particles[i].getX();      // x
        data[i * 6 + 1] = particles[i].getY();  // y
        data[i * 6 + 2] = particles[i].getZ();  // z
        data[i * 6 + 3] = particles[i].getVx(); // vx
        data[i * 6 + 4] = particles[i].getVy(); // vy
        data[i * 6 + 5] = particles[i].getVz(); // vz
    }

    // Write data to the dataset
    dataset.write(data.data(), H5::PredType::NATIVE_FLOAT);
}
