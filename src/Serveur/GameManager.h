#ifndef GAMAMANAGER_H__
#define GAMAMANAGER_H__

#include "pch.h"
#include <SFML/Graphics.hpp>
#include <map>
#include "Player.h"

class GameLevel {
public:


    GameLevel();
    void Init(); // Initialise le niveau

    void Update(); // Met à jour l'état du niveau

protected:

    std::map<int, Player*> pPlayer;


    SpriteClass mSpriteBackground;
    sf::RectangleShape mFadeOverlay;

    Vector2 mSizeObstacle;

    sf::Font mFont;

    sf::Text mScoreText;      // Texte pour afficher le score

    int mWindowHeight, mWindowWidth;
    int mNumObstacle;
    int nMaxBrickHP;

private:
    
};

#endif