#ifndef ENTITY_H__
#define ENTITY_H__

#include "Vector2.h"

class Entity
{
protected:

	Vector2 Position;
	float Speed;
	Vector2 Size;

public:
	Entity();

	void SetPosition(Vector2 _Position);
	Vector2 GetPosition();

	void SetSpeed(float _Speed);
	float GetSpeed();

	void SetSize(Vector2 _Size);
	Vector2 GetSize();

	Vector2 GetConstPosition() const;
	Vector2 GetConstSize() const;

	void SpawnEntity(Vector2 _Position);
};
#endif