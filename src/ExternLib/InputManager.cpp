#include "pch.h"
#include "InputManager.h"

InputManager::InputManager() {
    // Initialisation des touches A-Z
    for (char c = 'A'; c <= 'Z'; ++c) {
        keyStates[c] = None;  // Initialiser l'état de chaque touche à "None"
    }

    mouseStates[VK_LBUTTON] = None;  // Clic gauche
    mouseStates[VK_RBUTTON] = None;  // Clic droit
}

void InputManager::update() {
    // Mettre à jour les états des touches
    for (auto it = keyStates.begin(); it != keyStates.end(); ++it) {
        int key = it->first;        // Clé (code de la touche)
        KeyState& state = it->second;  // État de la touche

        SHORT keyState = GetAsyncKeyState(key);

        if (keyState & 0x8000) { // Touche enfoncée
            if (state == None || state == Up)
                state = Push;
            else
                state = Down;
        }
        else { // Touche relâchée
            if (state == Down || state == Push)
                state = Up;
            else
                state = None;
        }
    }

    // Mettre à jour l'état des boutons de la souris (clic gauche et droit)
    for (auto it = mouseStates.begin(); it != mouseStates.end(); ++it) {
        int button = it->first;
        KeyState& state = it->second;

        SHORT buttonState = GetAsyncKeyState(button);

        if (buttonState & 0x8000) { // Bouton enfoncé
            if (state == None || state == Up)
                state = Push;
            else
                state = Down;
        }
        else { // Bouton relâché
            if (state == Down || state == Push)
                state = Up;
            else
                state = None;
        }
    }
}

KeyState InputManager::getKeyState(int key) const {
    auto it = keyStates.find(key);
    if (it != keyStates.end())
        return it->second;
    return None;
}

KeyState InputManager::getMouseState(int button) const {
    auto it = mouseStates.find(button);
    if (it != mouseStates.end())
        return it->second;
    return None;
}