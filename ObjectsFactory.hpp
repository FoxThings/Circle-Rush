#include "Renderer.hpp"

class ObjectsFactory {
public:
	ObjectsFactory(Renderer* renderer);
	~ObjectsFactory() = default;

	GameObject* Instantiate(Vector2D position, BoxCollider shape);
	void Destroy(GameObject* object);
private:
	Renderer* renderer;
};
