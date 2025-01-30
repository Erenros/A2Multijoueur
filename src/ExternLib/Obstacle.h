#ifndef OBSTACLE_H__
#define OBSTACLE_H__

#include "Vector2.h"
#include "Entity.h"
#include "Sprite.h"

class Obstacle : public Entity
{
protected:

	bool mData = false;
	SpriteClass* mSpriteObstacle;

public:

	Obstacle();
	~Obstacle();

	int Init(SpriteClass* _Sprite, const Vector2 _Size, const Vector2 _Position, float _Rotation, float _Speed, int _Hp);

	void SetSprite(SpriteClass* _Sprite);
	SpriteClass* GetSprite();

	sf::Sprite GetSfSprite() const;
	
};

#endif