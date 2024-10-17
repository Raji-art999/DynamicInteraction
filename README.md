

**DynamicInteraction** is a project that simulates and visualizes a simple particle system, focusing on interactions and dynamics. This project leverages **OpenGL** for real-time rendering, **Boost** for multithreading, and **HDF5** for storing simulation data. 

## Features

- **Real-time Visualization**: Utilizes OpenGL to render particles and their interactions in real-time.
- **Multithreaded Computation**: Employs Boost libraries to parallelize the calculation of particle positions, enhancing performance and responsiveness.
- **Data Storage**: Uses HDF5 to efficiently save and retrieve particle data at each simulation time step, allowing for detailed analysis and visualization of particle behavior.

## Technologies Used

- **C++**: The programming language used for the simulation.
- **OpenGL**: For rendering 2D/3D graphics.
- **Boost**: A set of C++ libraries that provide support for multithreading.
- **HDF5**: A file format and set of tools for managing complex data.

## Getting Started

### Prerequisites

Ensure you have the following installed on your machine:

- C++ compiler (e.g., g++, clang++)
- CMake (for building the project)
- OpenGL and GLFW (for rendering)
- Boost library (for multithreading)
- HDF5 library (for data storage)

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/yourusername/dynamicinteraction.git
   cd dynamicinteraction

