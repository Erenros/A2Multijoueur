#ifndef MAP_H__
#define MAP_H__

#include "Window.h"

class Map {
public:

    Map();
    ~Map();

    void CreateObstacles(int _numObstacle);
    void SetView(const sf::Vector2f& position, const sf::Vector2f& size);

private:
    sf::RenderWindow m_window;     
    sf::View m_view;
};

#endif
