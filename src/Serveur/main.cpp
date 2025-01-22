#include "pch.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Vector2.h"
#include <iostream>

int main() {
    // Dimensions de la fenêtre
    const float windowWidth = 800.0f;
    const float windowHeight = 600.0f;

    // Création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Test Player");

    // Vérification si la fenêtre est bien ouverte
    if (!window.isOpen()) {
        std::cout << "Échec de l'ouverture de la fenêtre !" << std::endl;
        return -1;
    }

    // Gestionnaire d'entrées
    InputManager inputManager;

    // Création et initialisation du sprite pour le joueur
    SpriteClass playerSprite;

    // Création et initialisation du joueur
    Player player;

    // Crée un objet Vector2 avec le constructeur vide et initialisation après création
    Vector2 size;
    size.Init(50.0f, 50.0f);  // Taille du joueur
    Vector2 position;
    position.Init(375.0f, 550.0f);  // Position initiale du joueur

    player.Init(&playerSprite, &inputManager, size, position, 0.10f, 100);

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Gestion des entrées via InputManager
            inputManager.HandleEvent(event);
        }

        // Mettre à jour la position du joueur
        player.Move(windowWidth, windowHeight);

        // Dessiner la scène
        window.clear();  // Effacer l'écran

        // Si le sprite n'est pas initialisé, afficher un rectangle
        if (player.GetSprite() == nullptr) {
            // Créer un rectangle pour représenter le joueur
            sf::RectangleShape rectangle(sf::Vector2f(size.GetX(), size.GetY()));
            rectangle.setFillColor(sf::Color::Green);  // Remplacer par la couleur de votre choix
            rectangle.setPosition(player.GetPosition().GetX(), player.GetPosition().GetY());
            window.draw(rectangle);
        }
        else {
            // Affichage du sprite si il est correctement initialisé
            sf::Sprite& sprite = player.GetSprite()->GetSprite();
            sprite.setPosition(player.GetPosition().GetX(), player.GetPosition().GetY());
            window.draw(sprite);
        }

        window.display();  // Afficher la scène à l'écran
    }

    // Nettoyage
    player.Uninit();
    playerSprite.Uninit();

    return 0;
}
