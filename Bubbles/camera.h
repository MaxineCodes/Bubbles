#pragma once

#include "scene.h"

class camera
{
private:
    point3 origin;
    point3 lower_left_corner;
    vector3 horizontal;
    vector3 vertical;

public:

    // Constructor
    camera()
    {
        // Image variables
        auto aspect_ratio = scene::image_width / scene::image_height;
        auto viewport_height = 2.0;
        auto viewport_width = aspect_ratio * viewport_height;

        // Camera variables
        //double focal_length = scene::focal_length;
        double focal_length = 1.0;

        origin = point3(0, 0, 0);
        horizontal = vector3(viewport_width, 0.0, 0.0);
        vertical = vector3(0.0, viewport_height, 0.0);
        lower_left_corner = origin - horizontal / 2 - vertical / 2 - vector3(0, 0, focal_length);
    }

    ray get_ray(double u, double v) const 
    {
        return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }
};
