#ifndef INPUTMANAGER_H__
#define INPUTMANAGER_H__

#include <unordered_map>
#include <Windows.h>

enum KeyState {
    None,   // Aucune action sur la touche
    Push,   // Touche pressée (début)
    Down,   // Touche maintenue enfoncée
    Up      // Touche relâchée
};

class InputManager {
private:
    std::unordered_map<int, KeyState> keyStates;  // Remplacer sf::Keyboard::Key par int (VK_*)
    std::unordered_map<int, KeyState> mouseStates; // Ajouter un map pour les boutons de la souris

public:
    InputManager();

    void update();  // Mise à jour sans événement SFML, à appeler dans la boucle de jeu

    // Récupère l'état d'une touche spécifique
    KeyState getKeyState(int key) const;

    // Récupère l'état d'un bouton de la souris
    KeyState getMouseState(int button) const;
};

#endif