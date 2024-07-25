#include "Renderer.hpp"
#include "Simulation.hpp"

class ObjectsFactory {
public:
	ObjectsFactory(Renderer* renderer, Simulation* simulation);
	~ObjectsFactory() = default;

	GameObject* Instantiate(Vector2D position, Sprite* sprite, BoxCollider shape);
	void Destroy(GameObject* object);
private:
	Renderer* renderer;
	Simulation* simulation;
};
