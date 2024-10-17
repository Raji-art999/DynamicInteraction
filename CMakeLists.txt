cmake_minimum_required(VERSION 3.10)
project(ParticleSimulation)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find necessary packages
find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)
find_package(GLFW3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(HDF5 REQUIRED COMPONENTS CXX)  # Add HDF5 support

# Manually set GLEW_LIBRARY if it is not found
if(NOT GLEW_LIBRARY)
    set(GLEW_LIBRARY /opt/homebrew/lib/libGLEW.dylib)
endif()

# Include directories
include_directories(
    ${GLFW_INCLUDE_DIRS} 
    ${GLEW_INCLUDE_DIRS} 
    ${HDF5_INCLUDE_DIRS}  # Include HDF5 directories
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src  # Add src directory for custom headers
)

# Add source files
set(SOURCES
    main.cpp
    src/ParticleSystem.cpp
)

# Create executable
add_executable(ParticleSimulation ${SOURCES})

# Link libraries
target_link_libraries(ParticleSimulation 
    ${OPENGL_LIBRARIES} 
    ${GLEW_LIBRARY}  
    glfw 
    ${Boost_LIBRARIES}
    ${HDF5_LIBRARIES}  # Link HDF5 libraries
)
