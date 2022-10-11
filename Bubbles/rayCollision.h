#pragma once

#include "utils.h"


struct objectRecord 
{
    point3 p;
    vector3 normal;
    double t{};

    // Calculate normal face
    bool frontFace{};
    inline void setFaceNormal(const ray& _ray, const vector3& outward_normal)
    {
        frontFace = dot(_ray.direction(), outward_normal) < 0;
        normal = frontFace ? outward_normal : -outward_normal;
    }
};

class collidable 
{
public:
    virtual bool hit(const ray& _ray, double t_min, double t_max, objectRecord& rec) const = 0;
};

// List of ray-collidable objects 
class objectList : public collidable 
{
public:
    // Public variables
    std::vector<std::shared_ptr<collidable>> objects;
public:
    // Public functions
    objectList();
    objectList(std::shared_ptr<collidable> object);
    virtual bool hit(const ray& _ray, double t_min, double t_max, objectRecord& rec) const override;
    void clear();
    void add(std::shared_ptr<collidable> object);
};