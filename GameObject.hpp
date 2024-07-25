#pragma once

#include <cstdint>
#include "BoxCollider.hpp"

class GameObject {
	friend class Renderer;
	friend class Simulation;
public:
	GameObject() = default;
	GameObject(Vector2D position, BoxCollider collider);

	void Move(Vector2D delta);
	void SetPosition(Vector2D newPosition);

	uint32_t color = 851515;

    BoxCollider collider;

private:
	Vector2D position;
};
