#pragma once

#include <cstdint>
#include "BoxCollider.hpp"
#include "Sprite.hpp"

class GameObject {
	friend class Renderer;
	friend class Simulation;
public:
	GameObject() = default;
	GameObject(Vector2D position, Sprite* sprite, BoxCollider collider);

	void Move(Vector2D delta);
	void SetPosition(Vector2D newPosition);

    BoxCollider collider;

private:
	Vector2D position;
	Sprite* sprite;
};
