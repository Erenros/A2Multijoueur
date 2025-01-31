#include "pch.h"
#include "Projectile.h"
#include <iostream>

Projectile::Projectile() : pSpriteProjectile(nullptr), mDamage(0), mIndexDeplacement(-1), mOwner("")
{
}

Projectile::~Projectile()
{
}

void Projectile::Init(SpriteClass* _Sprite, const Vector2& _Size, const Vector2& _Position, int _IndexDepl, float _Speed, int _Damage, const std::string& _Owner)
{
    this->pSpriteProjectile = _Sprite;

    sf::Vector2u textureSize = pSpriteProjectile->GetSprite().getTexture()->getSize();
    Vector2 size;
    size.Init(static_cast<float>(textureSize.x), static_cast<float>(textureSize.y));
    SetSize(size);

    SetSize(_Size);
    SetPosition(_Position);
    SetSpeed(_Speed);

    mIndexDeplacement = _IndexDepl;
    mDamage = _Damage;
    mOwner = _Owner;
}

void Projectile::Uninit()
{
    mDamage = 0;
    pSpriteProjectile = nullptr;
}

int Projectile::GetDamage() const
{
    return mDamage;
}

void Projectile::SetDamage(int _Damage)
{
    mDamage = _Damage;
}

void Projectile::SetSprite(SpriteClass* _Sprite)
{
    pSpriteProjectile = _Sprite;
}

SpriteClass* Projectile::GetSprite()
{
    return pSpriteProjectile;
}

void Projectile::Move(float _DeltaTime)
{
    float moveSpeed = GetSpeed() * _DeltaTime;
    Vector2 currentPosition = GetPosition();

    switch (mIndexDeplacement)
    {
    case 0:
        currentPosition.SetX(currentPosition.GetX() + moveSpeed);
        break;
    case 1:
        currentPosition.SetX(currentPosition.GetX() - moveSpeed);
        break;
    case 2:
        currentPosition.SetY(currentPosition.GetY() - moveSpeed);
        break;
    case 3:
        currentPosition.SetY(currentPosition.GetY() + moveSpeed);
        break;
    default:
        break;
    }

    SetPosition(currentPosition);

    // Affiche la position pour le débogage
    std::cout << "Projectile Position - X: " << currentPosition.GetX()
        << ", Y: " << currentPosition.GetY() << std::endl;
}
