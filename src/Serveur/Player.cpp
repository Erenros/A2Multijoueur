#include "pch.h"
#include "Player.h"
#include <iostream>

Player::Player() : SpritePlayer(nullptr), Hp(6), Data(nullptr), Speed(20.0f), Size(Vector2()), Position(Vector2()), InputPlayer(nullptr)
{
}

Player::~Player()
{
}

void Player::Init(SpriteClass* _Sprite, InputManager* _InputPlayer, const Vector2& _Size, const Vector2& _Position, float _Speed, int _Hp)
{

    InputPlayer = _InputPlayer;
    this->SpritePlayer = _Sprite;

    if (!Data) {
        Data = new int(Hp);
        std::cout << "Resource reinitialized with value: " << *Data << "\n";
    }

    SetSize(_Size);
    SetPosition(_Position);
    SetSpeed(_Speed);

    /*SpritePlayer->GetSprite().setScale(
        _Size.GetX() / SpritePlayer->GetTexture().getSize().x,
        _Size.GetY() / SpritePlayer->GetTexture().getSize().y
    );*/
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

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) && CurrentPosition.GetX() > 0) {
        CurrentPosition.SetX(CurrentPosition.GetX() - PlayerSpeed);
    }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && CurrentPosition.GetX() + PlayerSize.GetX() < _WindowWidth) {
        CurrentPosition.SetX(CurrentPosition.GetX() + PlayerSpeed);
    }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && CurrentPosition.GetY() > 0) {
        CurrentPosition.SetY(CurrentPosition.GetY() - PlayerSpeed);
    }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && CurrentPosition.GetY() + PlayerSize.GetY() < _WindowHeight) {
        CurrentPosition.SetY(CurrentPosition.GetY() + PlayerSpeed);
    }

    this->SetPosition(CurrentPosition);
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
