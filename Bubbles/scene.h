#pragma once

#include "vector3.h"
#include "rayCollision.h"
#include "bubble.h"
#include "utils.h"


// Scene world where objects are placed
objectList sceneObjectList;

// Scene class is a collection class of the image, camera, and world data
class scene
{
public:
	// Image variables
	static const int image_width = 800;
	static const int image_height = 400;
	static const int aspect_ratio = image_width / image_height;
	static const int raytraceSamples = 2;

	// Camera variables

	// World variables
	
};

void populateScene() 
{
	sceneObjectList.add(std::make_shared<bubble>(point3(0, 0, -1), 0.5));
	sceneObjectList.add(std::make_shared<bubble>(point3(0, -5.5, -1), 5));
}

//std::shared_ptr<scene> Scene;
//Scene = std::make_shared<scene>(0);