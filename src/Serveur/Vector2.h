#ifndef VECTOR2_H__
#define VECTOR2_H__


class Vector2 {

    float x;
    float y;

public:

    Vector2();

    void Init(float _x, float _y);

    float GetX() const;
    float GetY() const;
    void SetX(float _x);
    void SetY(float _y);

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