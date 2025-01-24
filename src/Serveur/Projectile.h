#ifndef PROJECTILE_H__
#define PROJECTILE_H__

#include <SFML/Graphics.hpp>

class Projectile {

    int mSpeed, mDmg;
    sf::RectangleShape mShape;

public:

    Projectile();
    ~Projectile();

    void Init(int _Speed, int _Damage);

    void Move(int _IndexDirection);
    void Death();
    bool CheckCollisions();
    void CreateProjectile();
    void Update(float Deltatime);
};

#endif