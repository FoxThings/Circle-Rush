#include "Renderer.hpp"

Renderer::Renderer(uint32_t* buffer, uint32_t width, uint32_t height) : ObjectsHolder(), buffer(buffer), width(width), height(height) { }

void Renderer::Update()
{
	memset(buffer, 0, width * height * sizeof(uint32_t));

	for (std::vector<GameObject*>::iterator it = objects->begin(); it != objects->end(); ++it) {
		Vector2D size = (*it)->collider.size;

		// Center pivot coordinate system to UpLeftCorner
		Vector2D position = (*it)->position - size * 0.5;

		// left-down corned coordinate system
		for (int y = int(height - position.y - size.y); y < int(height - position.y); ++y) {
			for (int x = int(position.x); x < int(position.x + size.x); ++x) {
				if (
					(x >= 0 && x < width) &&
					(y >= 0 && y < height))
				{
					buffer[y * width + x] = (*it)->color;
				}
			}
		}
	}
}
