#include "GameObject.hpp"

GameObject::GameObject(Vector2D position, BoxCollider shape): position(position), shape(shape) { }

void GameObject::Move(Vector2D delta)
{
	this->position += delta;
}

void GameObject::Render(uint32_t* buffer, uint32_t width, uint32_t height)
{
	Vector2D size = this->shape.size;
	Vector2D position = this->position;
	
	for (uint32_t y = (uint32_t)position.y; y < position.y + size.y; ++y) {
		for (uint32_t x = (uint32_t)position.x; x < position.x + size.x; ++x) {
			if (
				(x > 0 && x < width) && 
				(y > 0 && y < height)) 
			{
				buffer[x * width + y] = 4515146844685;
			}
		}
	}
}
