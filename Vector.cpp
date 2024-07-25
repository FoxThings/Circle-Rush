#include "Vector.hpp"

#include <cmath>

Vector2D::Vector2D(float x, float y) : x(x), y(y) {}

Vector2D& Vector2D::operator+=(const Vector2D& other) {
	x += other.x;
	y += other.y;
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2D& Vector2D::operator*=(float num) {
	x *= num;
	y *= num;
	return *this;
}

Vector2D& Vector2D::operator-() { return (*this *= -1); }

Vector2D& Vector2D::Normalize()
{
	float magnitute = std::sqrt((*this) * (*this));
	x /= magnitute;
	y /= magnitute;

	return *this;
}

long long operator*(const Vector2D& first, const Vector2D& second) {
	return first.x * second.x + first.y * second.y;
}

Vector2D operator+(const Vector2D& first, const Vector2D& second) {
	Vector2D temp(first);
	temp += second;
	return temp;
}

Vector2D operator-(const Vector2D& first, const Vector2D& second) {
	Vector2D temp(first);
	temp -= second;
	return temp;
}

long long operator^(const Vector2D& first, const Vector2D& second) {
	return first.x * second.y - second.x * first.y;
}

Vector2D operator*(const Vector2D& vec, float num) {
	Vector2D temp(vec);
	temp *= num;
	return temp;
}

Vector2D operator*(float num, const Vector2D& vec) { return (vec * num); }

bool operator==(const Vector2D& first, const Vector2D& second) {
	return (first.x == second.x && first.y == second.y);
}
