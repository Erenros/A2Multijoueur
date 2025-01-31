#include "pch.h"
#include "Map.h"

Map::Map() : mViewArea(0.f, 0.f, 800.f, 600.f), mPlayerPosition(400.f, 300.f) {}

Map::~Map() {}

void Map::Init(int _width, int _height, const std::string& title) {
    // Configurer les dimensions de la carte
    mViewArea.width = static_cast<float>(_width);
    mViewArea.height = static_cast<float>(_height);

    // Configurer le titre de la carte (optionnel)
    std::cout << "Carte initialisée : " << title << std::endl;
}

void Map::Draw(sf::RenderWindow& _Window) {
    _Window.clear();

    // Calculer la transformation nécessaire pour "afficher" la vue
    sf::Transform transform;
    transform.translate(-mPlayerPosition.x + mViewArea.width / 2.f, -mPlayerPosition.y + mViewArea.height / 2.f);

    // Dessiner la carte avec la transformation
    if (mSpriteMap) {
        _Window.draw(mSpriteMap->GetSprite(), transform);
    }
    else {
        std::cerr << "Erreur : mSpriteMap est null !" << std::endl;
    }
}

void Map::UpdateCamera(const sf::Vector2f& playerPosition, float width, float height) {
    mPlayerPosition = playerPosition;

    // Appliquer les limites de la carte (en pixels)
    float mapWidth = 2000.f;  // Largeur de la carte
    float mapHeight = 2000.f;  // Hauteur de la carte

    float halfWidth = width / 2.f;
    float halfHeight = height / 2.f;

    // Ajuster la position de la caméra pour ne pas sortir des limites de la carte
    if (mPlayerPosition.x - halfWidth < 0.f)
        mPlayerPosition.x = halfWidth;
    if (mPlayerPosition.x + halfWidth > mapWidth)
        mPlayerPosition.x = mapWidth - halfWidth;

    if (mPlayerPosition.y - halfHeight < 0.f)
        mPlayerPosition.y = halfHeight;
    if (mPlayerPosition.y + halfHeight > mapHeight)
        mPlayerPosition.y = mapHeight - halfHeight;
}

void Map::setPosition(const Vector2& position) {
    mMapShape.setPosition(position.ToSFMLVectorF());
}

void Map::SetSprite(SpriteClass* _Sprite) {
    mSpriteMap = _Sprite;
}

SpriteClass* Map::GetSprite() {
    return mSpriteMap;
}

void Map::Render(sf::RenderWindow& window, const sf::Transform& transform) {
    if (mSpriteMap) {
        // Dessiner la carte avec la transformation
        window.draw(mSpriteMap->GetSprite(), transform);
    }
    else {
        std::cerr << "Erreur : mSpriteMap est null !" << std::endl;
    }
}