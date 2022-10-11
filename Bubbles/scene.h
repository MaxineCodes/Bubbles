#pragma once

#include "rayCollision.h"
#include "bubble.h"


// Scene class is a collection class of the image, camera, and world data
class scene
{
public:
	// Render variables
	static const bool antialiasingEnabled = true;
	static const bool normalDebugMode = false;

	// Image variables
	static const int image_width = 800;
	static const int image_height = 400;
	double aspect_ratio = image_width / image_height;
	static const int raytraceSamples = 5;

	// Camera variables
	double focal_length = 1.0;

	// World variables

public:
	// Public functions
	static void populate(objectList);
};