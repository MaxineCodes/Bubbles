#pragma once

#include <cmath>
#include <iostream>


// __________________________________________________________________________________________________________________________
// Vector3 Struct
struct vector3
{
	double e[3];

	// Colour
	vector3() : e{ 0,0,0 } {}
	// 3D Coords
	vector3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }

	vector3 operator-() const {
		return vector3(-e[0], -e[1], -e[2]);
	}
	double operator[](int i) const {
		return e[i];
	}
	double& operator[](int i) {
		return e[i];
	}

	vector3& operator+=(const vector3& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	vector3& operator*=(const double t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	vector3& operator/=(const double t)
	{
		return *this *= 1 / t;
	}

	double length() const
	{
		return std::sqrt(length_squared());
	}

	double length_squared() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}
	inline static vector3 random() 
	{
		return vector3(randomDouble(), randomDouble(), randomDouble());
	}

	inline static vector3 random(double min, double max) 
	{
		return vector3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
	}

	bool near_zero() const 
	{
		// Return true if the vector is close to zero in all dimensions.
		const auto s = 1e-8;
		return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
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

static vector3 random_in_unit_sphere() 
{
	while (true) 
	{
		auto p = vector3::random(-1, 1);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}

static vector3 random_unit_vector() 
{
	return unit_vector(random_in_unit_sphere());
}

static vector3 reflect(const vector3& v, const vector3& n) 
{
	return v - 2 * dot(v, n) * n;
}

static vector3 refract(const vector3& uv, const vector3& n, double etai_over_etat) 
{
	auto cos_theta = fmin(dot(-uv, n), 1.0);
	vector3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
	vector3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
	return r_out_perp + r_out_parallel;
}

static vector3 random_in_unit_disk() 
{
	while (true) 
	{
		auto p = vector3(randomDouble(-1, 1), randomDouble(-1, 1), 0);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}