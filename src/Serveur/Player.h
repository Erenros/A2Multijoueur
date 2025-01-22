#ifndef PLAYER_H__
#define PLAYER_H__

#include "Vector2.h"
#include "Entity.h"
#include "Sprite.h"
#include "InputManager.h"

class Player : public Entity

{
protected:
	SpriteClass* SpritePlayer;
	InputManager* InputPlayer;

	int Hp;
	int* Data;
	float Speed;

	const Vector2 Size;
	const Vector2 Position;


public:
	Player();
	~Player();

	void Init(SpriteClass* _Sprite,	InputManager* _InputPlayer, const Vector2& _Size, const Vector2& _Position, float _Speed, int _Hp);
	void Uninit();

	void Move(float _WindowWidth, float _WindowHeight);
	void TakeDammage(int _Dmg);

	int GetHp();

	void SetSprite(SpriteClass* _Sprite);
	SpriteClass* GetSprite();

};

#endif
