#include "GameObject.hpp"

GameObject::GameObject(Vector2D position, BoxCollider shape): position(position), collider(shape) { }

void GameObject::Move(Vector2D delta)
{
	this->position += delta;
}

void GameObject::SetPosition(Vector2D newPosition)
{
	this->position = newPosition;
}
