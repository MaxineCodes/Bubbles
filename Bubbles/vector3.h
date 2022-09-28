#pragma once

#include <cmath>
#include <iostream>

using std::sqrt;


// __________________________________________________________________________________________________________________________
// Vector3 Class
class vector3 
{
public:

    float e[3];

public:

    // Colour
    vector3() : e{ 0,0,0 } {}
    // 3D Coords
    vector3(float e0, float e1, float e2) : e{ e0, e1, e2 } {}

    float x() const { return e[0]; }
    float y() const { return e[1]; }
    float z() const { return e[2]; }

    vector3 operator-() const { 
        return vector3(-e[0], -e[1], -e[2]); 
    }
    float operator[](int i) const { 
        return e[i]; 
    }
    float& operator[](int i) { 
        return e[i]; 
    }

    vector3& operator+=(const vector3& v) 
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vector3& operator*=(const float t) 
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vector3& operator/=(const float t) 
    {
        return *this *= 1 / t;
    }

    float length() const 
    {
        return sqrt(length_squared());
    }

    float length_squared() const 
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }
};

// Type aliases for vector3
using point3 = vector3; // 3D Coords
using colour = vector3; // RGB Colour


// __________________________________________________________________________________________________________________________
// Vector3 Utility Functions
inline std::ostream& operator<<(std::ostream& out, const vector3& v) 
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vector3 operator+(const vector3& u, const vector3& v) 
{
    return vector3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vector3 operator-(const vector3& u, const vector3& v) 
{
    return vector3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vector3 operator*(const vector3& u, const vector3& v) 
{
    return vector3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vector3 operator*(double t, const vector3& v) 
{
    return vector3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vector3 operator*(const vector3& v, double t) 
{
    return t * v;
}

inline vector3 operator/(vector3 v, double t) {
    return (1 / t) * v;
}

inline double dot(const vector3& u, const vector3& v) 
{
    return u.e[0] * v.e[0]
        + u.e[1] * v.e[1]
        + u.e[2] * v.e[2];
}

inline vector3 cross(const vector3& u, const vector3& v) 
{
    return vector3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vector3 unit_vector(vector3 v) 
{
    return v / v.length();
}