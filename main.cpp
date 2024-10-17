#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ParticleSystem.h"
#include <iostream>

// Function to render particles
void renderParticles(const ParticleSystem& system) {
    const auto& particles = system.getParticles();

    glBegin(GL_POINTS);
    for (const auto& p : particles) {
        // Use getters to access x, y, z
        glVertex3f(p.getX(), p.getY(), p.getZ());
    }
    glEnd();
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    // Create GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Particle Simulation", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        std::cerr << "Failed to create GLFW window!" << std::endl;
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
        return -1;
    }

    // Set up OpenGL settings
    glPointSize(5.0f);
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering

    // Initialize particle system with 1000 particles
    ParticleSystem particleSystem(1000); 

    float lastTime = glfwGetTime();
    float timeAccumulator = 0.0f;
    float timeStep = 0.01f;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Timing
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // Update particles
        timeAccumulator += deltaTime;
        while (timeAccumulator >= timeStep) {
            particleSystem.updateParticles(timeStep);
            timeAccumulator -= timeStep;
        }

        // Render particles
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderParticles(particleSystem);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Save particle data to HDF5 before exiting
    particleSystem.saveToHDF5("particle_data.h5");

    // Clean up and exit
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
