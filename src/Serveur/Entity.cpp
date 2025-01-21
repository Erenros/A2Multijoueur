#include "pch.h"
#include "Entity.h"

Entity::Entity()
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