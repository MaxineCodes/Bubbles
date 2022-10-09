#include "bubble.h"


// Class constructor
bubble::bubble(point3 _center, double _radius) : center(_center), radius(_radius)
{

}


bool bubble::hit(const ray& _ray, double t_min, double t_max, objectRecord& rec) const
{
    vector3 oc = _ray.origin() - center;
    auto a = _ray.direction().length_squared();
    auto half_b = dot(oc, _ray.direction());
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) 
    {
        return false;
    }

    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) 
    {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root) 
        {
            return false;
        }
    }

    rec.t = root;
    rec.p = _ray.at(rec.t);
    vector3 outward_normal = (rec.p - center) / radius;
    rec.setFaceNormal(_ray, outward_normal);

    return true;
}
