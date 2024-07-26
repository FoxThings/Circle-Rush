#include "GameObject.hpp"

GameObject::GameObject(Vector2D position, Sprite* sprite, BoxCollider collider): position(position), sprite(sprite), collider(collider) { }

void GameObject::Move(Vector2D delta)
{
	this->position += delta;
}

void GameObject::SetPosition(Vector2D newPosition)
{
	this->position = newPosition;
}

void GameObject::ChangeSprite(Sprite* sprite)
{
	this->sprite = sprite;
}
