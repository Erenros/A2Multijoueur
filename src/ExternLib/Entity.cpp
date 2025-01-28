#include "pch.h"
#include "Entity.h"

Entity::Entity() :mPosition(Vector2()), mSpeed(0.0f), mSize(Vector2())
{
}

Entity::~Entity()
{
}

void Entity::SetPosition(Vector2 Position) {
    this->mPosition = Position;
}

Vector2 Entity::GetPosition() {
    return this->mPosition;
}

void Entity::SetSpeed(float Speed) {
    this->mSpeed = Speed;
}

float Entity::GetSpeed() {
    return this->mSpeed;
}

void Entity::SetSize(Vector2 Size) {
    this->mSize = Size;
}

Vector2 Entity::GetSize() {
    return this->mSize;
}

Vector2 Entity::GetConstPosition() const {
    return mPosition;
}

Vector2 Entity::GetConstSize() const {
    return mSize;
}

void Entity::SpawnEntity(Vector2 _Position)
{
}

bool Entity::CollisionAABB(Entity* other) const {

	float left1 = GetConstPosition().GetX();
	float top1 = GetConstPosition().GetY();
	float right1 = left1 + GetConstSize().GetX();
	float bottom1 = top1 + GetConstSize().GetY();

	float left2 = other->GetConstPosition().GetX();
	float top2 = other->GetConstPosition().GetY();
	float right2 = left2 + other->GetConstSize().GetX();
	float bottom2 = top2 + other->GetConstSize().GetY();

	return !(right1 < left2 ||
		left1 > right2 ||
		bottom1 < top2 ||
		top1 > bottom2);
}
