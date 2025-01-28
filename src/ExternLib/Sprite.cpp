#include "pch.h"
#include "Sprite.h"
#include <iostream>

// Initialise la classe Sprite avec le chemin de l'image du sprite et charge l'image
SpriteClass::SpriteClass() :mSpritePath(""), pData(nullptr)
{
}

void SpriteClass::Init(const std::string _SpritePath)
{
    mSpritePath = _SpritePath;
    if (!pData) {
        pData = new std::string(_SpritePath);
        std::cout << "Resource initialized with value: " << *pData << std::endl;
    }
    if (!LoadImage(_SpritePath)) {
        std::cerr << "Erreur : Impossible d'initialiser le sprite avec '" << _SpritePath << "'" << std::endl;
    }
}

void SpriteClass::Uninit()
{
    if (pData) {
        std::cout << "Resource uninitialized, value was: " << *pData << std::endl;
        delete pData;
        pData = nullptr;
    }
}

bool SpriteClass::LoadImage(std::string _SpritePath)
{
    // Tente de charger l'image et applique la texture au sprite si reussi
    if (mTextureSprite.loadFromFile(mSpritePath))
    {
        mSpriteS.setTexture(mTextureSprite); // Applique la texture au sprite
        return true;
    }
    else {
        std::cerr << "Erreur : Impossible de charger l'image ? partir de '" << _SpritePath << "'" << std::endl;
        return false;
    }
}

const sf::Texture& SpriteClass::GetTexture()
{
    return mTextureSprite;
}

sf::Sprite& SpriteClass::GetSprite() {
    return mSpriteS;
}

void SpriteClass::SetSprite(sf::Sprite _NewSprite) {
    mSpriteS = _NewSprite;
}