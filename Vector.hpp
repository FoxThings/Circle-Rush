#pragma once

class Vector2D {
public:
	Vector2D() = default;
	Vector2D(float x, float y);

	Vector2D& operator+=(const Vector2D& other);
	Vector2D& operator-=(const Vector2D& other);
	Vector2D& operator*=(float num);
	Vector2D& operator-();

	friend long long operator*(const Vector2D& first, const Vector2D& second);
	friend long long operator^(const Vector2D& first, const Vector2D& second);
	friend Vector2D operator*(const Vector2D& vec, float num);
	friend Vector2D operator*(float num, const Vector2D& vec);
	friend Vector2D operator-(const Vector2D& first, const Vector2D& second);
	friend Vector2D operator+(const Vector2D& first, const Vector2D& second);
	friend bool operator==(const Vector2D& first, const Vector2D& second);

	float x;
	float y;
};
