#pragma once

#include "Vector.hpp"
#include <functional>

class BoxCollider {
	friend class Simulation;
public:
	BoxCollider() = default;
	BoxCollider(Vector2D size, std::function<void(BoxCollider*, BoxCollider*)> callback = nullptr);

	Vector2D size;

private:
	std::function<void(BoxCollider*, BoxCollider*)> callback;
};
