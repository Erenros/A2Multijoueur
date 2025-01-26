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
#include "Obstacle.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Vector2.h"
#include <iostream>
#include <filesystem> // Pour gérer les chemins dynamiquement

#include "pch.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Obstacle.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Vector2.h"
#include <iostream>
#include <filesystem> // Pour gérer les chemins dynamiquement

int main() {

    //  -------------------------------------   INIT   -------------------------------------
    // Dimensions de la fenêtre
    const float windowWidth = 1260.0f;
    const float windowHeight = 800.0f;

    // Création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Test Player");
    window.setFramerateLimit(60);

    // Vérification si la fenêtre est bien ouverte
    if (!window.isOpen()) {
        std::cout << "Échec de l'ouverture de la fenêtre !" << std::endl;
        return -1;
    }

    // Gestionnaire d'entrées
    InputManager inputManager;

    // ------------- Création et initialisation des sprites -------------
    SpriteClass playerSprite;
    SpriteClass obstacleSprite;

    // Définir le chemin relatif dynamiquement
    std::string basePath = std::filesystem::current_path().parent_path().parent_path().string();

    // ------------- Création du joueur -------------
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

    Player player;

    // Récupérer la taille du sprite du joueur et prendre en compte la mise à l'échelle
    sf::Vector2u textureSize = texture.getSize();  // Taille de la texture du joueur

    // Appliquer la mise à l'échelle si nécessaire
    sf::Vector2f scale = playerSprite.GetSprite().getScale();
    Vector2 size;
    size.Init(static_cast<float>(textureSize.x) * scale.x, static_cast<float>(textureSize.y) * scale.y);

    Vector2 position;
    position.Init(375.0f, 550.0f);

    player.Init(&playerSprite, &inputManager, size, position, 10.10f, 100);

    // ------------- Création d'un obstacle -------------
    Obstacle obstacle;

    // Charger une texture pour l'obstacle
    std::string obstacleTexturePath = basePath + "/sprite/Obstacle.png";
    sf::Texture obstacleTexture;
    if (!obstacleTexture.loadFromFile(obstacleTexturePath)) {
        std::cout << "Erreur : Impossible de charger l'image de l'obstacle '" << obstacleTexturePath << "' !" << std::endl;
        return -1; // Arrêter l'exécution en cas d'erreur
    }
    obstacleSprite.GetSprite().setTexture(obstacleTexture);

    // Prendre la taille du sprite pour l'obstacle
    sf::Vector2u obstacleTextureSize = obstacleTexture.getSize();

    // Appliquer la mise à l'échelle si nécessaire
    sf::Vector2f obstacleScale = obstacleSprite.GetSprite().getScale();
    Vector2 sizeObstacle;
    sizeObstacle.Init(static_cast<float>(obstacleTextureSize.x) * obstacleScale.x, static_cast<float>(obstacleTextureSize.y) * obstacleScale.y);

    Vector2 positionObstacle;
    positionObstacle.Init(500.0f, 400.0f); // Position initiale de l'obstacle
    obstacle.Init(&obstacleSprite, sizeObstacle, positionObstacle, 0.0f, 0.0f, 100);

    //  -------------------------------------   GAME LOOP   -------------------------------------

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Enregistrer la position actuelle du joueur
        Vector2 previousPosition = player.GetPosition();

        // Mettre à jour la position du joueur
        player.Move(windowWidth, windowHeight);

        // Vérifier les collisions
        if (player.CollisionAABB(&obstacle)) {
            std::cout << "Collision détectée entre le joueur et l'obstacle !" << std::endl;
            // Revenir à la position précédente
            player.SetPosition(previousPosition);
        }

        // Dessiner la scène
        window.clear();  // Effacer l'écran

        // Dessiner le sprite du joueur avec la texture chargée
        sf::Sprite& sprite = player.GetSprite()->GetSprite();
        sprite.setPosition(player.GetPosition().GetX(), player.GetPosition().GetY());
        window.draw(sprite);

        // Dessiner l'obstacle avec sa texture
        sf::Sprite obstacleSfSprite = obstacle.GetSfSprite();
        obstacleSfSprite.setPosition(positionObstacle.GetX(), positionObstacle.GetY());
        window.draw(obstacleSfSprite);

        window.display();  // Afficher la scène à l'écran
    }

    //  -------------------------------------   UNINIT   -------------------------------------
    player.Uninit();
    playerSprite.Uninit();

    return 0;
}

