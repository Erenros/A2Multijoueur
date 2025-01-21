#include "pch.h"
#include "Entity.h"

Entity::Entity() :Position(Vector2()), Speed(0.0f), Size(Vector2())
{
}

void Entity::SetPosition(Vector2 Position) {
    this->Position = Position;
}

Vector2 Entity::GetPosition() {
    return this->Position;
}

void Entity::SetSpeed(float Speed) {
    this->Speed = Speed;
}

float Entity::GetSpeed() {
    return this->Speed;
}

void Entity::SetSize(Vector2 Size) {
    this->Size = Size;
}

Vector2 Entity::GetSize() {
    return this->Size;
}

Vector2 Entity::GetConstPosition() const {
    return Position;
}

Vector2 Entity::GetConstSize() const {
    return Size;
}

void Entity::SpawnEntity(Vector2 _Position)
{
}
