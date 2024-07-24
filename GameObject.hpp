#pragma once

#include "BoxCollider.hpp"
#include "Vector.hpp"
#include <cstdint>

class GameObject {
	friend class Renderer;
public:
	GameObject() = default;
	GameObject(Vector2D position, BoxCollider shape);

	void Move(Vector2D delta);
	void SetPosition(Vector2D newPosition);

private:
	Vector2D position;
	BoxCollider shape;
};
