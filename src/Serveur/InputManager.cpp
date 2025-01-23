#include "pch.h"
#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager() {}

void InputManager::HandleEvent(const sf::Event& event) {
    switch (event.type) {
    case sf::Event::KeyPressed:
        bKeyStates[event.key.code] = true;
        break;

    case sf::Event::KeyReleased:
        bKeyStates[event.key.code] = false;
        break;

    case sf::Event::MouseButtonPressed:
        bMouseStates[event.mouseButton.button] = true;
        break;

    case sf::Event::MouseButtonReleased:
        bMouseStates[event.mouseButton.button] = false;
        break;

    default:
        break;
    }
}

bool InputManager::IsKeyPressed(sf::Keyboard::Key key) const {
    auto it = bKeyStates.find(key);
    if (it != bKeyStates.end()) {
        return it->second;
    }
    return false;
}

bool InputManager::IsMouseButtonPressed(sf::Mouse::Button button) const {
    auto it = bMouseStates.find(button);
    if (it != bMouseStates.end()) {
        return it->second;
    }
    return false;
}

sf::Vector2i InputManager::GetMousePosition(const sf::RenderWindow& window) const {
    return sf::Mouse::getPosition(window);
}
