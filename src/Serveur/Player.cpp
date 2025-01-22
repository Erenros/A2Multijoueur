#include "pch.h"
#include "Player.h"
#include <iostream>

Player::Player() : Hp(6), Data(nullptr)
{
}

Player::~Player()
{
}

void Player::Init()
{
    if (!Data) {
        Data = new int(Hp);
        std::cout << "Resource reinitialized with value: " << *Data << "\n";
    }

    SetSize(Size);
    SetPosition(Position);
    SetSpeed(Speed);
}

void Player::Uninit()
{
    if (Data) {
        std::cout << "Resource uninitialized, value was: " << *Data << "\n";
        delete Data;
        Data = nullptr;
    }
}

void Player::Move(float _WindowWidth, float _WindowHeight)
{
    float PlayerSpeed = this->GetSpeed();
    Vector2 CurrentPosition = this->GetPosition();
    Vector2 PlayerSize = this->GetSize();
}

void Player::TakeDammage(int _Dmg)
{
    Hp -= _Dmg;
    if (Hp < 0) {
        Hp = 0;
    }
}

int Player::GetHp()
{
    return Hp;
}

void Player::SetSprite(SpriteClass* _Sprite)
{
    SpritePlayer = _Sprite;
}

SpriteClass* Player::GetSprite()
{
    return SpritePlayer;
}
