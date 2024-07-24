#include "Renderer.hpp"

Renderer::Renderer(uint32_t* buffer, uint32_t width, uint32_t height) : buffer(buffer), width(width), height(height) {
	objects = new std::list<GameObject*>;
}

Renderer::~Renderer()
{
	objects->clear();
	free(objects);
}

void Renderer::AddObject(GameObject* object)
{
	objects->push_back(object);
}

void Renderer::RemoveObject(GameObject* object)
{
	std::list<GameObject*>::iterator item = std::find(objects->begin(), objects->end(), object);
	if (objects->end() != item)
	{
		objects->erase(item);
	}
}

void Renderer::Update()
{
	memset(buffer, 0, width * height * sizeof(uint32_t));

	for (std::list<GameObject*>::iterator it = objects->begin(); it != objects->end(); ++it) {
		Vector2D size = (*it)->shape.size;

		// Center pivot coordinate system
		Vector2D position = (*it)->position - size * 0.5;

		// left-down corned coordinate system
		for (int y = height - (int)position.y - size.y; y < height - position.y; ++y) {
			for (int x = (int)position.x; x < position.x + size.x; ++x) {
				if (
					(x >= 0 && x < width) &&
					(y >= 0 && y < height))
				{
					buffer[y * width + x] = 4515146844685;
				}
			}
		}
	}
}
