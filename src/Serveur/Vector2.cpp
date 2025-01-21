#include "pch.h"
#include "Vector2.h"

Vector2::Vector2() : x(0.0f), y(0.0f)
{
}

float Vector2::GetX() const
{
	return this->x;
}

float Vector2::GetY() const
{
	return this->y;
}

void Vector2::SetX(float _x)
{
	this->x = _x;
}

void Vector2::SetY(float _y)
{
	this->y = _y;
}

void Vector2::SpawnEntity(float _x, float _y)
{
}

Vector2& Vector2::Subtract(const Vector2& _other) {
    this->x -= _other.x;
    this->y -= _other.y;
    return *this;
}

Vector2& Vector2::Add(const Vector2& _other) {
    this->x += _other.x;
    this->y += _other.y;
    return *this;
}

Vector2& Vector2::Multiplay(const Vector2& _other) {
    this->x *= _other.x;
    this->y *= _other.y;
    return *this;
}

Vector2& Vector2::Divide(const Vector2& _other) {
    this->x /= _other.x;
    this->y /= _other.y;
    return *this;
}


