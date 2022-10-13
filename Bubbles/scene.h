#pragma once

#include "rayCollision.h"
#include "bubble.h"


// Scene class is a collection class of the image, camera, and world data
// The GUI will write to this class, and the raytrace algorithm will read from this class
// This class is used as an intermediate to organize data IO
class scene
{
public:
	// Global raytrace settings

	// Render variables
	bool antialiasingEnabled = true; // Default = true
	bool normalDebugMode = false; // Default = false
	bool rayBouncesEnabled = true; // Default = true ----- Currently unused
	int maxRayDepth = 10;

	// Image variables
	int image_width = 200;
	int image_height = 100;
	int raytraceSamples = 25;
	double aspect_ratio = image_width / image_height;

public:
	// Scene object settings

	// World
	objectList world;

public:
	// Constructor
	scene() 
	{

	}

public:
	// Public functions

	// Populates the scene with all objects
	static void populate()
	{
		objectList scene;
	}

	// Adds a new bubble object to the scene
	static void add(point3 position, double radius, std::shared_ptr<material> material)
	{

	}
};