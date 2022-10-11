#pragma once

// Std includes
#include <cmath>
#include <limits>
#include <memory>
#include <vector>
#include <random>

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;


//// Utility Functions

// Turn degrees(360) to radians(180)
inline double degreesToRadians(double degrees) 
{
    return degrees * pi / 180.0;
}

// Random doubles
inline double randomDouble() 
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
// Random double with min-max
inline double randomDouble(double min, double max) 
{
    return min + (max - min) * randomDouble();
}

// Clamping
inline double clamp(double value, double min, double max) 
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}


// Raytrace includes
#include "ray.h"
#include "vector3.h"