#ifndef PROJECTILE_H__
#define PROJECTILE_H__

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Sprite.h"
#include <string>

class Projectile : public Entity
{
private:
    SpriteClass* pSpriteProjectile;
    int mDamage;
    int mIndexDeplacement;
    std::string mOwner;

public:
    Projectile();
    ~Projectile();

    void Init(SpriteClass* _Sprite, const Vector2& _Size, const Vector2& _Position, int _IndexDepl, float _Speed, int _Damage, const std::string& _Owner);
    void Uninit();

    int GetDamage() const;
    void SetDamage(int _Damage);

    void SetSprite(SpriteClass* _Sprite);
    SpriteClass* GetSprite();

    void Move(float _DeltaTime);
};

#endif
