#pragma once


#include <iostream>
#include <QImage>

// Raytracing includes
#include "vector3.h"
#include "scene.h"
#include "utils.h"

// Images
QImage QImage32bit	(scene::image_width, scene::image_height, QImage::Format_RGB32);
QImage QImage8bit	(scene::image_width, scene::image_height, QImage::Format_Indexed8);

// Declare helper functions
colour rayColour(const ray& _ray, const collidable& _world);
void writeQImage32(int x, int y, colour pixelColour);
float hit_sphere(const point3& center, float radius, const ray& _ray);


// Main rendering function
void raytrace()
{
	populateScene();

	// Image
	static int image_width	= scene::image_width;
	static int image_height = scene::image_height;
	static int aspect_ratio = scene::aspect_ratio;

	// Camera
	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;

	auto origin = point3(0, 0, 5);
	auto horizontal = vector3(viewport_width, 0, 0);
	auto vertical = vector3(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vector3(0, 0, focal_length);


	// Render
	//std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
	for (int h = image_height - 1; h >= 0; h--)
	{
		//std::cerr << "\rScanlines remaining: " << h << ' ' << std::flush;
		for (int w = 0; w < image_width; w++)
		{
			// 2D coords "uv" 
			auto u = float(w) / (image_width - 1);
			auto v = float(h) / (image_height - 1);

			ray _ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			colour pixelColour = rayColour(_ray, sceneObjectList);
		
			// Write image
			writeQImage32(w, h, pixelColour);
		}
	}
	QImage32bit = QImage32bit.mirrored(false, true);
	//std::cerr << "\nDone.\n";.
}


// ________Helper functions________

// Ray colour
colour rayColour(const ray& _ray, const collidable& _world)
{
	// Ray hits object in scenObjectList(_world)
	objectRecord rec;
	if (_world.hit(_ray, 0, infinity, rec)) 
	{
		return 0.5 * (rec.normal + colour(1, 1, 1));
	}
	vector3 unit_direction = unit_vector(_ray.direction());
	float t = 0.5 * (unit_direction.y() + 1.0);

	// Image gradient: First colour = bottom, second colour = top
	return (1.0 - t) * colour(0.0, 0.0, 0.0) + t * colour(1.0, 1.0, 1.0);
}

// Image output as QImage 32 bit
void writeQImage32(int x, int y, colour pixelColour)
{
	// Translate float[0.0, 1.0] values to int[0, 255] byte value
	int r = 255.999 * pixelColour.x();
	int g = 255.999 * pixelColour.y();
	int b = 255.999 * pixelColour.z();

	// Write colour to image
	QRgb colour = qRgb(r, g, b);
	QImage32bit.setPixel(x, y, colour);
}


float hit_sphere(const point3& center, float radius, const ray& _ray) 
{
	vector3 oc = _ray.origin() - center;

	auto a = _ray.direction().length_squared();
	auto half_b = dot(oc, _ray.direction());
	auto c = oc.length_squared() - radius * radius;
	auto discriminant = half_b * half_b - a * c;

	if (discriminant < 0) 
	{
		return -1.0;
	}
	else 
	{
		return (-half_b - sqrt(discriminant)) / a;
	}
}