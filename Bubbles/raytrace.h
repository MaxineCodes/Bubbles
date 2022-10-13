#pragma once


#include <iostream>
#include <QImage>

// Qt includes
#include "bubblesgui.h"

// Raytracing includes
#include "utils.h"
#include "scene.h"
#include "camera.h"
#include "material.h"

// Qt Gui public variables
int progressbarProgress;
// Image
QImage QImage32bit(100, 100, QImage::Format_RGB32);

// Helper function declarations
colour rayColour(const ray& _ray, const collidable& _world, int depth, bool normalDebugMode);
void writeQImage32(int x, int y, colour pixelColour, int samples);
void write_color(std::ostream& out, colour pixel_color, int samples_per_pixel);
double hit_sphere(const point3& center, double radius, const ray& _ray);


// Main rendering function
void raytrace(scene Scene, camera cam, int samples)
{
	QImage32bit = QImage32bit.scaled(Scene.image_width, Scene.image_height);

	// Materials
	auto material_ground = std::make_shared<lambert>(colour(0.1, 0.1, 0.1));
	auto material_center = std::make_shared<lambert>(colour(0.9, 0.9, 0.9));
	auto material_left = std::make_shared<dielectric>(1.5);
	auto material_right = std::make_shared<metallic>(colour(0.9, 0.9, 0.9), 0.20);

	// Bubbles
	Scene.world.add(std::make_shared<bubble>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
	Scene.world.add(std::make_shared<bubble>(point3(0.0, 0.0, -1.0), 0.5, material_center));
	Scene.world.add(std::make_shared<bubble>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
	Scene.world.add(std::make_shared<bubble>(point3(1.0, 0.0, -1.0), 0.5, material_right));

	// Render
	static bool antialiasing = Scene.antialiasingEnabled;

	// Image
	static int image_width	= Scene.image_width;
	static int image_height = Scene.image_height;
	static double aspect_ratio = Scene.aspect_ratio;
	const int max_depth = Scene.maxRayDepth;

	// Camera
	point3 lookfrom(0, 1, 8);
	point3 lookat(0, 0.25, -1);
	vector3 vup(0, 1, 0);
	auto dist_to_focus = (lookfrom - lookat).length();
	auto aperture = 0.0;

	//camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);


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
				pixelColour += rayColour(_ray, Scene.world, max_depth, Scene.normalDebugMode);
			}
			// Write QImage
			writeQImage32(x, y, pixelColour, samples);
			// Mirror image after it's been generated
			//QImage32bit = QImage32bit.mirrored(false, true);
			//bubblesGui::setViewportImage(QImage32bit);
			//bubblesGui::setProgressbarValue(image_height);


		}
	}
	// Mirror image after it's been generated
	QImage32bit = QImage32bit.mirrored(false, true);
	//std::cerr << "\nDone.\n";
}


// ________Helper functions________

// Ray colour
colour rayColour(const ray& _ray, const collidable& _world, int depth, bool normalDebugMode)
{
	// Ray hits object in scenObjectList(_world)

	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
		return colour(0, 0, 0);

	objectRecord rec;
	if (_world.hit(_ray, 0.0001, infinity, rec)) 
	{
		// Render normals-only if normalDebugMode is true
		if (normalDebugMode)
		{
			return 0.5 * (rec.normal + colour(1, 1, 1));
		}
		// Otherwise, render normally
		ray scattered;
		colour attenuation;
		if (rec.mat_ptr->scatter(_ray, rec, attenuation, scattered)) 
		{
			return attenuation * rayColour(scattered, _world, depth - 1, normalDebugMode);
		}
		return colour(0, 0, 0);
	}
	
	vector3 unit_direction = unit_vector(_ray.direction());
	double t = 0.5 * (unit_direction.y() + 1.0);

	// Image gradient: First colour = bottom, second colour = top
	return (1.0 - t) * colour(1.0, 0.0, 0.8) + t * colour(0.0, 0.5, 1.0);
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
	R = sqrt(scale * R);
	G = sqrt(scale * G);
	B = sqrt(scale * B);

	// Translate double[0.0, 1.0] values to int[0, 255] byte value
	R = 256 * clamp(R, 0.0, 0.999);
	G = 256 * clamp(G, 0.0, 0.999);
	B = 256 * clamp(B, 0.0, 0.999);
	
	// Write colour to image
	QRgb colour = qRgb(R, G, B);
	QImage32bit.setPixel(x, y, colour);
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