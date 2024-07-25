#include "ObjectsHolder.hpp"

ObjectsHolder::ObjectsHolder() {
	objects = new std::vector<GameObject*>;
}

ObjectsHolder::~ObjectsHolder()
{
	objects->clear();
	free(objects);
}

void ObjectsHolder::AddObject(GameObject* object)
{
	objects->push_back(object);
}

void ObjectsHolder::RemoveObject(GameObject* object)
{
	std::vector<GameObject*>::iterator item = std::find(objects->begin(), objects->end(), object);
	if (objects->end() != item)
	{
		objects->erase(item);
	}
}
