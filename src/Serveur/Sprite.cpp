#include "pch.h"
#include "Sprite.h"
#include <iostream>

// Initialise la classe Sprite avec le chemin de l'image du sprite et charge l'image
SpriteClass::SpriteClass() :SpritePath("")
{
}

void SpriteClass::Init(const std::string _SpritePath)
{
    SpritePath = _SpritePath;
    if (!LoadImage(_SpritePath)) {
        std::cerr << "Erreur : Impossible d'initialiser le sprite avec '" << _SpritePath << "'" << std::endl;
    }
}

void SpriteClass::Uninit()
{
}

bool SpriteClass::LoadImage(std::string _SpritePath)
{
    // Tente de charger l'image et applique la texture au sprite si reussi
    if (TextureSprite.loadFromFile(SpritePath))
    {
        SpriteS.setTexture(TextureSprite); // Applique la texture au sprite
        return true;
    }
    else {
        std::cerr << "Erreur : Impossible de charger l'image ? partir de '" << _SpritePath << "'" << std::endl;
        return false;
    }
}

const sf::Texture& SpriteClass::GetTexture()
{
    return TextureSprite;
}

sf::Sprite& SpriteClass::GetSprite() {
    return SpriteS;
}

void SpriteClass::SetSprite(sf::Sprite _NewSprite) {
    SpriteS = _NewSprite;
}