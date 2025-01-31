#include "pch.h"
#include "Vector2.h"

Vector2::Vector2() : x(0.0f), y(0.0f)
{

}

void Vector2::Init(float _x, float _y)
{
    this->x = _x;
    this->y = _y;
}

float Vector2::GetX() const
{
	return this->x;
}

float Vector2::GetY() const
{
	return this->y;
}

float Vector2::GetX()
{
    return this->x;
}

float Vector2::GetY()
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

sf::Vector2i Vector2::ToSFMLVectorI() const {
    return sf::Vector2i(static_cast<int>(x), static_cast<int>(y));
}

sf::Vector2f Vector2::ToSFMLVectorF() const {
    return sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
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

Vector2& Vector2::Multiply(const Vector2& _other) {
    this->x *= _other.x;
    this->y *= _other.y;
    return *this;
}

Vector2& Vector2::Divide(const Vector2& _other) {
    this->x /= _other.x;
    this->y /= _other.y;
    return *this;
}


