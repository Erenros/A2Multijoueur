#include "pch.h"
#include "Player.h"
#include <iostream>

Player::Player() : pSpritePlayer(nullptr), mHp(6), pData(nullptr), mSpeed(20.0f), mSize(Vector2()), mPosition(Vector2()), pInputPlayer(nullptr)
{
}

Player::~Player()
{
}

void Player::Init(SpriteClass* _Sprite, InputManager* _InputPlayer, const Vector2& _Size, const Vector2& _Position, float _Speed, int _Hp)
{

    pInputPlayer = _InputPlayer;
    this->pSpritePlayer = _Sprite;

    if (!pData) {
        pData = new int(mHp);
        std::cout << "Resource reinitialized with value: " << *pData << "\n";
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
    if (pData) {
        std::cout << "Resource uninitialized, value was: " << *pData << "\n";
        delete pData;
        pData = nullptr;
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
    mHp -= _Dmg;
    if (mHp < 0) {
        mHp = 0;
    }
}

int Player::GetHp()
{
    return mHp;
}

void Player::SetSprite(SpriteClass* _Sprite)
{
    pSpritePlayer = _Sprite;
}

SpriteClass* Player::GetSprite()
{
    return pSpritePlayer;
}
