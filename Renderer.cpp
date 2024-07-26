#include "Renderer.hpp"

Renderer::Renderer(uint32_t* buffer, uint32_t width, uint32_t height) : ObjectsHolder(), buffer(buffer), width(width), height(height) { }

void Renderer::Update()
{
	memset(buffer, 0, width * height * sizeof(uint32_t));

	for (std::vector<GameObject*>::iterator it = objects->begin(); it != objects->end(); ++it) {
		Sprite* sprite = (*it)->sprite;
		Vector2D size = Vector2D(sprite->width, sprite->height);

		// Center pivot coordinate system to UpLeftCorner
		Vector2D position = (*it)->position - size * 0.5;

		// left-down corned coordinate system
		for (int y = int(height - position.y - size.y), i = 0; y < int(height - position.y); ++y, ++i) {
			for (int x = int(position.x), j = 0; x < int(position.x + size.x); ++x, ++j) {
				if (
					(x >= 0 && x < width) &&
					(y >= 0 && y < height))
				{
					Pixel pixel = sprite->GetPixel(i, j);
					if (pixel.bgra.alpha > 0) {
						buffer[y * width + x] = pixel.pixel;
					}
				}
			}
		}
	}
}
