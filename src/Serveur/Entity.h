#ifndef ENTITY_H__
#define ENTITY_H__

#include "Vector2.h"

class Entity
{

protected:

	Vector2 mPosition;
	float mSpeed;
	Vector2 mSize;
	int mCollisionType;

	virtual void OnCollision(Entity* collidedWith) {};

public:
	Entity();
	~Entity();

	void SetPosition(Vector2 _Position);
	Vector2 GetPosition();

	void SetSpeed(float _Speed);
	float GetSpeed();

	void SetSize(Vector2 _Size);
	Vector2 GetSize();

	Vector2 GetConstPosition() const;
	Vector2 GetConstSize() const;

	void SpawnEntity(Vector2 _Position);

	enum collision {
		Circle,
		Square,
	};

	bool CollisionAABB(Entity* other) const;
};
#endif