#pragma once

#include "rayCollision.h"
#include "vector3.h"

// Bubble class
class bubble : public collidable 
{
public:
    // Public variables
    point3 center;
    float radius;

public:
    // Public functions
    bubble(point3 _center, double _radius);
    virtual bool hit(const ray& _ray, float t_min, float t_max, objectRecord& rec) const override;
};

