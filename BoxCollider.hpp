#pragma once

#include "Vector.hpp"

class BoxCollider {
public:
	BoxCollider() = default;
	BoxCollider(Vector2D size);

	Vector2D size;
};
