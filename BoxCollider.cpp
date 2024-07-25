#include "BoxCollider.hpp"

BoxCollider::BoxCollider(Vector2D size, std::function<void(BoxCollider*, BoxCollider*)> callback) : size(size), callback(callback) { }
