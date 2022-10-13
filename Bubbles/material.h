#pragma once

#include "utils.h"
#include "rayCollision.h"

struct objectRecord;

// Basic material class
class material 
{
public:
    // Public functions
    virtual bool scatter(const ray& r_in, const objectRecord& rec, colour& attenuation, ray& scattered) const = 0;
};


// Lambert material class
class lambert : public material 
{
public:
    // Constructor
    lambert(const colour& a) : albedo(a) 
    {

    }

public:
    // Public functions
    virtual bool scatter(const ray& r_in, const objectRecord& rec, colour& attenuation, ray& scattered) const override
    {
        auto scatter_direction = rec.normal + random_unit_vector();

        // Catch degenerate scatter direction
        if (scatter_direction.near_zero()) 
        {
            scatter_direction = rec.normal;
        }

        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }

public:
    colour albedo;
};


// Metal material class
class metallic : public material 
{
public:
    // Public variables
    colour albedo;
    double roughness;

public:
    // Constructor
    metallic(const colour& a, double f) : albedo(a), roughness(f < 1 ? f : 1)
    {
    
    }

public:
    // Public functions
    virtual bool scatter(const ray& r_in, const objectRecord& rec, colour& attenuation, ray& scattered) const override 
    {
        vector3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + roughness * random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
};


// Dielectric material class
class dielectric : public material 
{
public:
    // Public variables
    double refractionIndex; // Index of Refraction

public:
    // Constructor
    dielectric(double index_of_refraction) : refractionIndex(index_of_refraction) 
    {

    }

public:
    // Public functions
    virtual bool scatter(const ray& r_in, const objectRecord& rec, colour& attenuation, ray& scattered) const override
    {
        // Variables
        vector3 direction;
        vector3 unitDirection = unit_vector(r_in.direction());

        attenuation = colour(1.0, 1.0, 1.0);
        double refraction_ratio = rec.frontFace ? (1.0 / refractionIndex) : refractionIndex;

        double cos_theta = fmin(dot(-unitDirection, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0;

        // Refraction check
        if (cannot_refract || reflectance(cos_theta, refraction_ratio) > randomDouble())
        {
            direction = reflect(unitDirection, rec.normal);
        }
        else 
        {
            direction = refract(unitDirection, rec.normal, refraction_ratio);
        }

        scattered = ray(rec.p, direction);
        return true;
    }

private:
    // Private functions
    static double reflectance(double cosine, double ref_idx) 
    {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
};