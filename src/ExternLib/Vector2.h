#ifndef VECTOR2_H__
#define VECTOR2_H__

#include <SFML/System/Vector2.hpp>

class Vector2 {

    float x;
    float y;

public:

    Vector2();

    void Init(float _x, float _y);

    float GetX() const;
    float GetY() const;
    float GetX();
    float GetY();
    void SetX(float _x);
    void SetY(float _y);

    sf::Vector2i ToSFMLVectorI() const;
    sf::Vector2f ToSFMLVectorF() const;

    Vector2& Subtract(const Vector2& _other);
    Vector2& Add(const Vector2& _other);
    Vector2& Multiply(const Vector2& _other);
    Vector2& Divide(const Vector2& _other);

    //static Vector2 Subtract(const Vector2& _left, const Vector2& _right);
    //static Vector2 Add(const Vector2& _left, const Vector2& _right);
    //static Vector2 Multiply(const Vector2& _left, const Vector2& _right);
    //static Vector2 Divide(const Vector2& _left, const Vector2& _right);

};

#endif