//#include "pch.h"
//#include "Window.h"
//#include "Player.h"
//#include "InputManager.h"
//#include "Sprite.h"
//#include <SFML/Graphics.hpp>
//#include <iostream>
//
//int main() {
//    // Création de l'objet Window
//    Window window;
//    window.Init(1260, 800, "Test Player");
//
//    // Gestionnaire d'entrées
//    InputManager inputManager;
//
//    // Initialisation du joueur
//    SpriteClass playerSprite;
//    Player player;
//    Vector2 size;
//    size.Init(10.0f, 10.0f);
//    Vector2 position;
//    position.Init(10.0f, 10.0f);
//    player.Init(&playerSprite, &inputManager, size, position, 0.10f, 100);
//
//    // Boucle principale
//    while (window.getRenderWindow().isOpen()) {
//        sf::Event event;
//        while (window.getRenderWindow().pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.getRenderWindow().close();
//            }
//
//            inputManager.HandleEvent(event);
//        }
//
//        // Mettre à jour la position du joueur
//        player.Move(1260, 800);
//
//        // Dessiner la scène
//        window.Draw(window.getRenderWindow());
//
//        //// Afficher la barre de vie et le score
//        //window.DisplayPlayerHP(window.getRenderWindow(), player.GetHealth());
//        //window.LeaderBoard(window.getRenderWindow(), player.GetScore());
//
//        //window.getRenderWindow().display();  // Afficher les changements
//    }
//
//    // Nettoyage
//    player.Uninit();
//    playerSprite.Uninit();
//
//    return 0;
//}
#include "pch.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Vector2.h"
#include <iostream>
#include <filesystem> // Pour gérer les chemins dynamiquement

int main() {
    // Dimensions de la fenêtre
    const float windowWidth = 1260.0f;
    const float windowHeight = 800.0f;

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

    // Définir le chemin relatif dynamiquement
    std::string basePath = std::filesystem::current_path().parent_path().parent_path().string();
    std::string texturePath = basePath + "/sprite/Soldier.png";

    // Charger la texture pour le sprite
    sf::Texture texture;
    if (!texture.loadFromFile(texturePath)) {
        std::cout << "Erreur : Impossible de charger l'image '" << texturePath << "' !" << std::endl;
        return -1; // Arrêter l'exécution en cas d'erreur
    }

    std::cout << "Texture chargée depuis : " << texturePath << std::endl;

    // Appliquer la texture au sprite
    playerSprite.GetSprite().setTexture(texture);

    // Création et initialisation du joueur
    Player player;

    // Crée un objet Vector2 avec le constructeur vide et initialisation après création
    Vector2 size;
    size.Init(10.0f, 10.0f);  // Taille du joueur
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

        // Dessiner le sprite avec la texture chargée
        sf::Sprite& sprite = player.GetSprite()->GetSprite();
        sprite.setPosition(player.GetPosition().GetX(), player.GetPosition().GetY());
        window.draw(sprite);

        window.display();  // Afficher la scène à l'écran
    }

    // Nettoyage
    player.Uninit();
    playerSprite.Uninit();

    return 0;
}