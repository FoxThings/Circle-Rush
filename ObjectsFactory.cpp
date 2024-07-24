#include "ObjectsFactory.hpp"

ObjectsFactory::ObjectsFactory(Renderer* renderer): renderer(renderer) { }

GameObject* ObjectsFactory::Instantiate(Vector2D position, BoxCollider shape)
{
	GameObject* obj = new GameObject(position, shape);
	renderer->AddObject(obj);

	return obj;
}

void ObjectsFactory::Destroy(GameObject* object)
{
	renderer->RemoveObject(object);
}
