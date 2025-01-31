#include "pch.h"
#include "Player.h"
#include <iostream>

Player::Player() : pSpritePlayer(nullptr), pData(nullptr), mSpeed(20.0f), pInputPlayer(nullptr) {
    // Initialisation par défaut
}

Player::~Player() {
    Uninit();
}

void Player::Init(SpriteClass* _Sprite, InputManager* _InputPlayer, const Vector2& _Size, const Vector2& _Position, float _Speed, int _Hp) {
    pInputPlayer = _InputPlayer;
    pSpritePlayer = _Sprite;

    // Initialiser la taille et la position
    SetSize(_Size);
    SetPosition(_Position);
    SetSpeed(_Speed);

    // Initialiser la texture du sprite
    if (pSpritePlayer && pSpritePlayer->GetSprite().getTexture()) {
        sf::Vector2u textureSize = pSpritePlayer->GetSprite().getTexture()->getSize();
        Vector2 size;
        size.Init(static_cast<float>(textureSize.x), static_cast<float>(textureSize.y));
        SetSize(size);
    }

    // Initialiser les données supplémentaires
    if (!pData) {
        pData = new int(0); // Exemple d'initialisation
        std::cout << "Resource initialized with value: " << *pData << "\n";
    }
}

void Player::Uninit() {
    if (pData) {
        std::cout << "Resource uninitialized, value was: " << *pData << "\n";
        delete pData;
        pData = nullptr;
    }
}

void Player::Move(float _WindowWidth, float _WindowHeight) {
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

void Player::SetSprite(SpriteClass* _Sprite) {
    pSpritePlayer = _Sprite;
}

SpriteClass* Player::GetSprite() {
    return pSpritePlayer;
}

void Player::Render(sf::RenderWindow& window, const sf::Transform& transform) {
    if (pSpritePlayer) {
        // Mettre à jour la position du sprite
        pSpritePlayer->GetSprite().setPosition(GetPosition().GetX(), GetPosition().GetY());
        // Dessiner le sprite avec la transformation
        window.draw(pSpritePlayer->GetSprite(), transform);
    } else {
        std::cerr << "Erreur : pSpritePlayer est null !" << std::endl;
    }
}