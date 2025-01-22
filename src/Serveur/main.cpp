#include "pch.h"
#include "Window.h"
#include "Player.h"
#include "InputManager.h"
#include "Sprite.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Création de l'objet Window
    Window window;
    window.Init(1260, 800, "Test Player");

    // Gestionnaire d'entrées
    InputManager inputManager;

    // Initialisation du joueur
    SpriteClass playerSprite;
    Player player;
    Vector2 size;
    size.Init(10.0f, 10.0f);
    Vector2 position;
    position.Init(10.0f, 10.0f);
    player.Init(&playerSprite, &inputManager, size, position, 0.10f, 100);

    // Boucle principale
    while (window.getRenderWindow().isOpen()) {
        sf::Event event;
        while (window.getRenderWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.getRenderWindow().close();
            }

            inputManager.HandleEvent(event);
        }

        // Mettre à jour la position du joueur
        player.Move(1260, 800);

        // Dessiner la scène
        window.Draw(window.getRenderWindow());

        //// Afficher la barre de vie et le score
        //window.DisplayPlayerHP(window.getRenderWindow(), player.GetHealth());
        //window.LeaderBoard(window.getRenderWindow(), player.GetScore());

        //window.getRenderWindow().display();  // Afficher les changements
    }

    // Nettoyage
    player.Uninit();
    playerSprite.Uninit();

    return 0;
}
