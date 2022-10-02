#pragma once


#include <iostream>
#include <QImage>

// Raytracing includes
#include "vector3.h"
#include "scene.h"

// Images
QImage QImage32bit	(scene::image_width, scene::image_height, QImage::Format_RGB32);
QImage QImage8bit	(scene::image_width, scene::image_height, QImage::Format_Indexed8);


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
	point3 at(float t) const {
		return orig + t * dir;
	}
};


// Declare helper functions
colour rayColour(const ray& _ray);
void writeColour(std::ostream& out, colour pixelColour);

// Main rendering function
void raytrace()
{
	// Image
	static int image_width	= scene::image_width;
	static int image_height = scene::image_height;
	static int aspect_ratio = scene::aspect_ratio;
	//const auto aspect_ratio = 16.0 / 9.0;
	//const int image_height = static_cast<int>(image_width / aspect_ratio);


	// Camera
	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;

	auto origin = point3(0, 0, 0);
	auto horizontal = vector3(viewport_width, 0, 0);
	auto vertical = vector3(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vector3(0, 0, focal_length);


	// Render

	std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i)
		{
			// 2D coords "uv" 
			auto u = float(i) / (image_width - 1);
			auto v = float(j) / (image_height - 1);

			ray _ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			colour pixelColour = rayColour(_ray);

			writeColour(std::cout, pixelColour);
		}
	}

	std::cerr << "\nDone.\n";
}


// ________Helper functions________

// Ray colour
colour rayColour(const ray& _ray)
{
	vector3 unit_direction = unit_vector(_ray.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	// Image gradient: First colour = bottom, second colour = top
	return (1.0 - t) * colour(0.0, 0.8, 1.0) + t * colour(1.0, 0.0, 0.8);
}

// Image output colour as PPM
void writeColour(std::ostream& out, colour pixelColour)
{
	// Write the translated [0,255] value of each color component.
	out << static_cast<int>(255.999 * pixelColour.x()) << ' '
		<< static_cast<int>(255.999 * pixelColour.y()) << ' '
		<< static_cast<int>(255.999 * pixelColour.z()) << '\n';
}


void writeQImage32()
{
	// Preset colours
	constexpr QRgb c_Magenta		= qRgb(255, 0  , 255);
	constexpr QRgb c_Black		= qRgb(0  , 0  , 0  );

	// Fill with colour
	QImage32bit.fill(c_Black);

	// Testing setPixel
	for (int i = 0; i < 200; i++) 
	{
		QImage32bit.setPixel(i, i, c_Magenta);
		QImage32bit.setPixel(200, i, c_Magenta);
		QImage32bit.setPixel(i, 200, c_Magenta);
	}
}