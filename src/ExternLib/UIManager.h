#ifndef UIMANAGER_H__
#define UIMANAGER_H__

#include <SFML/Graphics.hpp>
#include <string>

class UIManager {
private:
    sf::RectangleShape mShape;
    sf::Text mText;
    sf::Font mFont;
    bool bIsHovered;
    bool bIsClicked;

public:
    UIManager();
    ~UIManager();

    void Init(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& buttonText, const sf::Font& font);
    void Uninit();

    void Draw(sf::RenderWindow& window);
    void Update(const sf::Vector2i& mousePos, bool isMousePressed);
    bool isPressed() const;

    std::string getText() const;
};

#endif