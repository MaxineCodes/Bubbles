#pragma once

#include "vector3.h"

// Ray class
class ray
{
public:
	point3 orig;
	vector3 dir;

public:
	ray() {}
	ray(const point3& origin, const vector3& direction) : orig(origin), dir(direction) {}

	point3 origin() const {
		return orig;
	}
	vector3 direction() const {
		return dir;
	}
	point3 at(double t) const {
		return orig + t * dir;
	}
};
