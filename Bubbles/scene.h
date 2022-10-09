#pragma once

#include "vector3.h"
#include "rayCollision.h"
#include "bubble.h"
#include "utils.h"


// Scene class is a collection class of the image, camera, and world data
class scene
{
public:
	// Render variables
	static const bool antialiasingEnabled = true;

	// Image variables
	static const int image_width = 400;
	static const int image_height = 200;
	double aspect_ratio = image_width / image_height;
	static const int raytraceSamples = 50;

	// Camera variables
	double focal_length = 1.0;

	// World variables

public:
	// Public functions
	static void populate(objectList);
};