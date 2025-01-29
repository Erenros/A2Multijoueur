#include "pch.h"
#include "Map.h"

Map::Map() : mViewArea(0.f, 0.f, 800.f, 600.f), mPlayerPosition(400.f, 300.f) {}

Map::~Map() {}

void Map::Init(int _width, int _height, const std::string& title) {
    // Pas besoin de définir une vue, juste gérer la taille de la fenêtre dans le main
    mViewArea.width = 800.f;  // Taille de la zone de vue
    mViewArea.height = 600.f;
}

void Map::Draw(sf::RenderWindow& _Window) {
    _Window.clear();

    // Calculer la transformation nécessaire pour "afficher" la vue
    sf::Transform transform;
    transform.translate(-mPlayerPosition.x + mViewArea.width / 2.f, -mPlayerPosition.y + mViewArea.height / 2.f);

    // Appliquer la transformation et dessiner les éléments
    //_Window.setView(sf::View(mPlayerPosition, sf::Vector2f(mViewArea.width, mViewArea.height)));
    // Dessiner ici les éléments de la carte (obstacles, ennemis, etc.)
    // _Window.draw(...);

    //_Window.display();
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

void Map::setPosition(const Vector2& position)
{
    mMapShape.setPosition(position.ToSFMLVectorF());
}

void Map::SetSprite(SpriteClass* _Sprite)
{
    mSpriteMap = _Sprite;
}

SpriteClass* Map::GetSprite()
{
    return mSpriteMap;
}

void Map::Render(sf::RenderWindow& window)
{
    window.draw(mSpriteMap->GetSprite());
}