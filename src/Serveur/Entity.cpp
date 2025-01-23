#include "pch.h"
#include "Entity.h"

Entity::Entity() :mPosition(Vector2()), mSpeed(0.0f), mSize(Vector2())
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
