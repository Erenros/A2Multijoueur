#ifndef PLAYER_H__
#define PLAYER_H__

#include "Vector2.h"
#include "Entity.h"
//#include "Sprite.h"

class Player : public Entity

{
protected:
	//SpriteClass* SpritePlayer;
	int Hp;
	int* data;

public:
	Player(/*SpriteClass* _Sprite,*/ const Vector2 _Size, const Vector2 _Position, float _Rotation, float _Speed, int _Hp);
	~Player();

	void Init();
	void Uninit();

	void Move(float _WindowWidth, float _WindowHeight);
	void TakeDammage(int _Dmg);


	/*void SetSprite(SpriteClass* _Sprite);
	SpriteClass* GetSprite();*/

};

#endif
