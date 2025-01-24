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

    if (!pData) {
        std::cout << "Resource reinitialized with value: " << *pData << "\n";
    }

    SetSize(_Size);
    SetPosition(_Position);
    SetSpeed(_Speed);

    /*SpritePlayer->GetSprite().setScale(
        _Size.GetX() / SpritePlayer->GetTexture().getSize().x,
        _Size.GetY() / SpritePlayer->GetTexture().getSize().y
    );*/

    return *pData;
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
