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

    void Init(int _width, int _height, const std::string& title);  // Init de la fenêtre
    void Draw(sf::RenderWindow& _Window);  // Dessine les éléments du niveau
    void UpdateCamera(const sf::Vector2f& playerPosition, float width, float height);  // Met à jour la caméra

    int Get_FinalScore();
    sf::RenderWindow& getRenderWindow();  // Accède à l'objet SFML RenderWindow

private:
    sf::View mView;  // La vue/caméra
};

#endif
