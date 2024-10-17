#ifndef PARTICLE_H
#define PARTICLE_H

class Particle {
private:
    float x, y, z;  // Position
    float vx, vy, vz; // Velocity
public:
    // Constructor to initialize position and velocity
    Particle(float x, float y, float z, float vx, float vy, float vz)
        : x(x), y(y), z(z), vx(vx), vy(vy), vz(vz) {}

    // Getters for position
    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }

    // Setters for position
    void setX(float newX) { x = newX; }
    void setY(float newY) { y = newY; }
    void setZ(float newZ) { z = newZ; }

    // Getters for velocity
    float getVx() const { return vx; }
    float getVy() const { return vy; }
    float getVz() const { return vz; }
};

#endif // PARTICLE_H
