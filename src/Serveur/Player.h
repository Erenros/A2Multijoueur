#ifndef PLAYER_H__
#define PLAYER_H__

#include "Vector2.h"
#include "Entity.h"
#include "LifeManager.h"
#include "Sprite.h"
#include "InputManager.h"
#include "ScoreManager.h"

class Player : public Entity, public LifeManager, public ScoreManager

{
protected:
	SpriteClass* pSpritePlayer;
	InputManager* pInputPlayer;

	int* pData;
	float mSpeed;

	const Vector2 mSize;
	const Vector2 mPosition;

public:
	Player();
	~Player();

	void Init(SpriteClass* _Sprite,	InputManager* _InputPlayer, const Vector2& _Size, const Vector2& _Position, float _Speed, int _Hp);
	void Uninit();

	void Move(float _WindowWidth, float _WindowHeight); //dois etre gérée par le serveur avec ClassInput

	void SetSprite(SpriteClass* _Sprite);
	SpriteClass* GetSprite();

};

#endif
