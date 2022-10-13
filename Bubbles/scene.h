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
	//static bool antialiasingEnabled; // Default = true
	//static bool normalDebugMode; // Default = false
	static bool rayBouncesEnabled; // Default = true ----- Currently unused
	static const bool antialiasingEnabled = true; // Default = true
	static const bool normalDebugMode = false; // Default = false

	// Image variables
	static const int image_width = 800;
	static const int image_height = 400;
	double aspect_ratio = image_width / image_height;
	static const int raytraceSamples = 5;

	//static QImage image();

public:
	// Scene object settings

	// World
	objectList world;

	// Bubbles
	// Some array[] of bubbles here

	// Materials
	// Some array[] of materials here

	// Camera variables
	static point3 position;
	static point3 viewDirection;
	static vector3 viewUp;
	static double aperture;

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
	static void addBubble() 
	{

	}

	// Adds a new material object to the scene
	static void addMaterial()
	{

	}
};