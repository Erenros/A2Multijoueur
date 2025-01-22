#include "pch.h"
#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager() {}

void InputManager::HandleEvent(const sf::Event& event) {
    switch (event.type) {
    case sf::Event::KeyPressed:
        KeyStates[event.key.code] = true;
        break;

    case sf::Event::KeyReleased:
        KeyStates[event.key.code] = false;
        break;

    case sf::Event::MouseButtonPressed:
        MouseStates[event.mouseButton.button] = true;
        break;

    case sf::Event::MouseButtonReleased:
        MouseStates[event.mouseButton.button] = false;
        break;

    default:
        break;
    }
}

bool InputManager::IsKeyPressed(sf::Keyboard::Key key) const {
    auto it = KeyStates.find(key);
    if (it != KeyStates.end()) {
        return it->second;
    }
    return false;
}

bool InputManager::IsMouseButtonPressed(sf::Mouse::Button button) const {
    auto it = MouseStates.find(button);
    if (it != MouseStates.end()) {
        return it->second;
    }
    return false;
}

sf::Vector2i InputManager::GetMousePosition(const sf::RenderWindow& window) const {
    return sf::Mouse::getPosition(window);
}
