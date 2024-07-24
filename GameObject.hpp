#pragma once

#include "BoxCollider.hpp"
#include "Vector.hpp"
#include <cstdint>

class GameObject {
public:
	GameObject() = default;
	GameObject(Vector2D position, BoxCollider shape);

	void Move(Vector2D delta);
	void Render(uint32_t* buffer, uint32_t width, uint32_t height);

private:
	Vector2D position;
	BoxCollider shape;
};
