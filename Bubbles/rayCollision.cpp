// Class include
#include "rayCollision.h"

// Class constructor
objectList::objectList()
{

}
// Another class constructor
objectList::objectList(std::shared_ptr<collidable> object)
{
    add(object);
}

// Object in objectList is hit
bool objectList::hit(const ray& _ray, double t_min, double t_max, objectRecord& rec) const
{
    objectRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects)
    {
        if (object->hit(_ray, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

// Clear the list
void objectList::clear()
{
    objects.clear();
}
// Add to the list
void objectList::add(std::shared_ptr<collidable> object)
{
    objects.push_back(object);
}