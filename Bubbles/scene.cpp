#include "scene.h"

// Populate the scene with objects
void scene::populate(objectList scene)
{
	scene.add(std::make_shared<bubble>(point3(0, 0, -1), 0.5));
	scene.add(std::make_shared<bubble>(point3(0, -5.5, -1), 5));
}