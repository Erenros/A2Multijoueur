#ifndef INPUTMANAGER_H__
#define INPUTMANAGER_H__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <unordered_map>

class InputManager
{
private:
    std::unordered_map<sf::Keyboard::Key, bool> KeyStates;
    std::unordered_map<sf::Mouse::Button, bool> MouseStates;
protected:

public:
	InputManager();
    ~InputManager();

    void HandleEvent(const sf::Event& event);
    bool IsKeyPressed(sf::Keyboard::Key key) const;
    bool IsMouseButtonPressed(sf::Mouse::Button button) const;
    sf::Vector2i GetMousePosition(const sf::RenderWindow& window) const;
};
#endif