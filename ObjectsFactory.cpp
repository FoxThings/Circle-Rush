#include "ObjectsFactory.hpp"

ObjectsFactory::ObjectsFactory(Renderer* renderer, Simulation* simulation): renderer(renderer), simulation(simulation) { }

GameObject* ObjectsFactory::Instantiate(Vector2D position, BoxCollider shape)
{
	GameObject* obj = new GameObject(position, shape);
	renderer->AddObject(obj);
	simulation->AddObject(obj);

	return obj;
}

void ObjectsFactory::Destroy(GameObject* object)
{
	renderer->RemoveObject(object);
	simulation->RemoveObject(object);
}
