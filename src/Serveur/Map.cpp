#include "pch.h"
#include "Map.h"

Map::Map() {}

Map::~Map() {}

void Map::Init(int _width, int _height, const std::string& title) {
    // Pas besoin de créer une nouvelle fenêtre ici, on la gère dans `main.cpp`
    mView.setSize(800.f, 600.f);  // Taille de la vue (caméra)
    mView.setCenter(400.f, 300.f);  // Initialement centré sur (400, 300)
}

void Map::Draw(sf::RenderWindow& _Window) {
    _Window.setView(mView);  // Appliquer la vue à la fenêtre principale
    _Window.clear();
    // Dessiner ici les éléments de la map (obstacles, ennemis, etc.)
   // _Window.display();
}

void Map::UpdateCamera(const sf::Vector2f& playerPosition, float width, float height) {
    // On déplace la vue de sorte que le joueur soit toujours au centre
    sf::Vector2f newCenter = playerPosition;

    // S'assurer que la caméra ne sort pas de la carte
    float mapWidth = 2000.f;  // Largeur de la carte (en pixels)
    float mapHeight = 2000.f;  // Hauteur de la carte

    float halfWidth = width / 2.f;
    float halfHeight = height / 2.f;

    // Vérifier les limites de la carte
    if (newCenter.x - halfWidth < 0.f)
        newCenter.x = halfWidth;
    if (newCenter.x + halfWidth > mapWidth)
        newCenter.x = mapWidth - halfWidth;

    if (newCenter.y - halfHeight < 0.f)
        newCenter.y = halfHeight;
    if (newCenter.y + halfHeight > mapHeight)
        newCenter.y = mapHeight - halfHeight;

    // Appliquer le déplacement de la caméra
    mView.setCenter(newCenter);
}

sf::RenderWindow& Map::getRenderWindow() {
    // Il n'est plus nécessaire de retourner une fenêtre ici
    throw std::logic_error("No need to access render window in Map anymore.");
}

int Map::Get_FinalScore() {
    return 0;
}
