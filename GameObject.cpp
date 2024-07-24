#include "GameObject.hpp"

GameObject::GameObject(Vector2D position, BoxCollider shape): position(position), shape(shape) { }

void GameObject::Move(Vector2D delta)
{
	this->position += delta;
}

void GameObject::SetPosition(Vector2D newPosition)
{
	this->position = newPosition;
}

void GameObject::Render(uint32_t* buffer, uint32_t width, uint32_t height)
{
	Vector2D size = this->shape.size;

	// Center pivot coordinate system
	Vector2D position = this->position - size * 0.5;
	
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
