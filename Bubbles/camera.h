#pragma once

#include "scene.h"

class camera
{
private:
    // Private variables
    point3 originPosition;
    point3 lower_left_corner;

    vector3 horizontal;
    vector3 vertical;
    vector3 u, v, viewVector;

    double lensSize;

public:
    // Constructor
    camera( point3 position, 
            point3 viewDirection, 
            vector3 viewUp, 
            double FOV, 
            double aspectRatio,
            double aperture, 
            double focusDistance)
    {
        // Image variables
        auto theta = degreesToRadians(FOV);
        auto h = tan(theta / 2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspectRatio * viewport_height;

        viewVector = unit_vector(position - viewDirection);
        u = unit_vector(cross(viewUp, viewVector));
        v = cross(viewVector, u);

        // Camera variables
        horizontal = focusDistance * viewport_width * u;
        vertical = focusDistance * viewport_height * v;
        lower_left_corner = originPosition - horizontal / 2 - vertical / 2 - focusDistance * viewVector;

        lensSize = aperture / 2;
        originPosition = position;
    }

    ray get_ray(double s, double t) const 
    {
        vector3 rd = lensSize * random_in_unit_disk();
        vector3 offset = u * rd.x() + v * rd.y();

        return ray(originPosition + offset, lower_left_corner + s * horizontal + t * vertical - originPosition - offset);
    }
};
