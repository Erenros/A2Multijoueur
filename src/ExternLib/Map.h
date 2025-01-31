#ifndef MAP_H__
#define MAP_H__

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Entity.h"
#include "Sprite.h"

class Map : public Entity, public SpriteClass {
public:
    Map();
    ~Map();

    void Init(int _width, int _height, const std::string& title);
    void Draw(sf::RenderWindow& _Window);
    void UpdateCamera(const sf::Vector2f& playerPosition, float width, float height);

    void setPosition(const Vector2& position);

    void SetSprite(SpriteClass* _Sprite);
    SpriteClass* GetSprite();
    void Render(sf::RenderWindow& window, const sf::Transform& transform);

    // Nouvelle méthode pour appliquer le décalage de la caméra
    sf::Vector2f ApplyCameraOffset(const sf::Vector2f& position);

private:
    sf::FloatRect mViewArea;
    sf::Vector2f mPlayerPosition;
    sf::RectangleShape mMapShape;
    SpriteClass* mSpriteMap;

    // Décalage de la caméra
    sf::Vector2f mCameraOffset;
};

#endif