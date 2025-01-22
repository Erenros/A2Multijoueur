#include "pch.h"
#include "Map.h"

Map::Map() {
    // Initialisation si nécessaire
}

Map::~Map() {
    // Libérer les ressources si nécessaire
}

void Map::CreateObstacles(int _numObstacle) {
    // Créer des obstacles sur la carte
}

void Map::SetView(const sf::Vector2f& position, const sf::Vector2f& size) {
    // Définir la vue pour afficher une portion de la carte
    m_view.setCenter(position);
    m_view.setSize(size);
    m_window.setView(m_view); // Applique la vue à la fenêtre
}