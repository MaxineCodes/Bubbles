#pragma once

#include "vector3.h"

// Scene class is a collection class of the image, camera, and world data
class scene
{
public:
	// Image variables
	static const int image_width = 400;
	static const int image_height = 400;
	static const int aspect_ratio = image_width / image_height;
	static const int raytraceSamples = 2;

	// Camera variables

	// World variables
};

//std::shared_ptr<scene> Scene;
//Scene = std::make_shared<scene>(0);