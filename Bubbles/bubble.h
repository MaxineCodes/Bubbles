#pragma once

#include "rayCollision.h"

// Bubble class
class bubble : public collidable 
{
public:
    // Public variables
    point3 center;
    double radius;
    std::shared_ptr<material> mat_ptr;

public:
    // Public functions
    bubble(point3 _center, double _radius, std::shared_ptr<material> _material);
    virtual bool hit(const ray& _ray, double t_min, double t_max, objectRecord& rec) const override;
};

