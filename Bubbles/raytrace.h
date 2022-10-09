#pragma once


#include <iostream>
#include <QImage>

// Raytracing includes
#include "vector3.h"
#include "utils.h"
#include "scene.h"
#include "camera.h"

// Images
QImage QImage32bit	(scene::image_width, scene::image_height, QImage::Format_RGB32);
//QImage QImage8bit	(scene::image_width, scene::image_height, QImage::Format_Indexed8);

// Declare helper functions
colour rayColour(const ray& _ray, const collidable& _world);
void writeQImage32(int x, int y, colour pixelColour, int samples);
void write_color(std::ostream& out, colour pixel_color, int samples_per_pixel);
double hit_sphere(const point3& center, double radius, const ray& _ray);


// Main rendering function
void raytrace()
{
	// Scene world where objects are placed
	objectList sceneObjectList;
	// Populate the scene world
	// Create instance of class
	scene Scene;
	//_scene.populate(sceneObjectList);
	sceneObjectList.add(std::make_shared<bubble>(point3(0, 0, -1), 0.5));
	sceneObjectList.add(std::make_shared<bubble>(point3(0, -5.5, -1), 5));

	// Render
	static bool antialiasing = Scene.antialiasingEnabled;

	// Image
	static int image_width	= Scene.image_width;
	static int image_height = Scene.image_height;
	static double aspect_ratio = Scene.aspect_ratio;
	const int samples = Scene.raytraceSamples;

	// Camera
	camera cam;


	// Render
	//std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
	for (int h = image_height - 1; h >= 0; h--)
	{
		//std::cerr << "\rScanlines remaining: " << h << ' ' << std::flush;
		for (int w = 0; w < image_width; w++)
		{
			// Define pixelColour
			colour pixelColour(0, 0, 0);

			int x = w; int y = h;

			// 2D coords "uv"
			for (int _sample = 0; _sample < samples; ++_sample)
			{
				double u, v;
				if (antialiasing) 
				{
					u = (w + randomDouble()) / (image_width - 1);
					v = (h + randomDouble()) / (image_height - 1);
				}
				if (!antialiasing) 
				{
					u = double(w) / (image_width - 1);
					v = double(h) / (image_height - 1);
				}
				

				ray _ray = cam.get_ray(u, v);
				pixelColour += rayColour(_ray, sceneObjectList);
			}
			// Write QImage
			writeQImage32(x, y, pixelColour, samples);
		}
	}
	// Mirror image after it's been generated
	QImage32bit = QImage32bit.mirrored(false, true);
	//std::cerr << "\nDone.\n";
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
	double t = 0.5 * (unit_direction.y() + 1.0);

	// Image gradient: First colour = bottom, second colour = top
	return (1.0 - t) * colour(0.0, 0.0, 0.0) + t * colour(1.0, 1.0, 1.0);
}

// Image output as QImage 32 bit
void writeQImage32(int x, int y, colour pixelColour, int samples)
{
	// Unpack RGB values from colour datatype
	auto R = pixelColour.x();
	auto G = pixelColour.y();
	auto B = pixelColour.z();
	
	// Divide the color by the number of samples.
	auto scale = 1.0 / samples;
	R *= scale;
	G *= scale;
	B *= scale;

	// Translate double[0.0, 1.0] values to int[0, 255] byte value
	R = 256 * clamp(R, 0.0, 0.999);
	G = 256 * clamp(G, 0.0, 0.999);
	B = 256 * clamp(B, 0.0, 0.999);
	
	// Write colour to image
	QRgb colour = qRgb(R, G, B);
	QImage32bit.setPixel(x, y, colour);

	// Debugging
	std::cout	<< static_cast<int>(256 * clamp(R, 0.0, 0.999)) << ' '
				<< static_cast<int>(256 * clamp(G, 0.0, 0.999)) << ' '
				<< static_cast<int>(256 * clamp(B, 0.0, 0.999)) << '\n';
}


double hit_sphere(const point3& center, double radius, const ray& _ray) 
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


void write_color(std::ostream& out, colour pixel_color, int samples_per_pixel) 
{
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	// Divide the color by the number of samples.
	auto scale = 1.0 / samples_per_pixel;
	r *= scale;
	g *= scale;
	b *= scale;

	// Write the translated [0,255] value of each color component.
	out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}