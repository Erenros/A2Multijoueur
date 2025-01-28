#include "pch.h"
#include "Obstacle.h"

Obstacle::Obstacle()
{
}

Obstacle::~Obstacle()
{
}

int Obstacle::Init(SpriteClass* _Sprite, const Vector2 _Size, const Vector2 _Position, float _Rotation, float _Speed, int _Hp)
{
    this->mSpriteObstacle = _Sprite;

    sf::Vector2u textureSize = mSpriteObstacle->GetSprite().getTexture()->getSize();
    Vector2 size;
    size.Init(static_cast<float>(textureSize.x), static_cast<float>(textureSize.y));
    SetSize(size);


    if (mData) {
        std::cout << "Resource initialized.\n";
    }

    mData = true;

    SetSize(_Size);
    SetPosition(_Position);
    SetSpeed(_Speed);

    /*SpritePlayer->GetSprite().setScale(
        _Size.GetX() / SpritePlayer->GetTexture().getSize().x,
        _Size.GetY() / SpritePlayer->GetTexture().getSize().y
    );*/

    return true;
}

void Obstacle::SetSprite(SpriteClass* _Sprite)
{
	mSpriteObstacle = _Sprite;
}

SpriteClass* Obstacle::GetSprite()
{
	return mSpriteObstacle;
}

sf::Sprite Obstacle::GetSfSprite() const
{
	return mSpriteObstacle->GetSprite(); // Retourne une copie du sprite
}
