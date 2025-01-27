#include "pch.h"
#include "UIManager.h"

UIManager::UIManager() : isHovered(false), isClicked(false) {}

UIManager::~UIManager() {}

void UIManager::Init(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& buttonText, const sf::Font& font) {
    // Initialisation de la forme du bouton
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Blue);  // Couleur par d?faut, ? personnaliser

    // Initialisation du texte du bouton
    text.setFont(font);
    text.setString(buttonText);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    // Centrer le texte sur le bouton
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    text.setPosition(position.x + size.x / 2, position.y + size.y / 2);
}

void UIManager::Uninit() {
    // Aucune ressource dynamique ? lib?rer dans cet exemple
}

void UIManager::Draw(sf::RenderWindow& window) {
    // Dessiner le bouton et son texte
    window.draw(shape);
    window.draw(text);
}

void UIManager::Update(const sf::Vector2i& mousePos, bool isMousePressed) {
    // V?rifier si la souris est sur le bouton
    isHovered = shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));

    // Si le bouton est survol?, changer de couleur
    if (isHovered) {
        shape.setFillColor(sf::Color::Green);  // Couleur lorsque la souris survole
    }
    else {
        shape.setFillColor(sf::Color::Blue);   // Couleur par d?faut
    }

    // V?rifier si la souris est cliqu?e
    if (isHovered && isMousePressed) {
        isClicked = true;  // Bouton cliqu?
    }
}

bool UIManager::isPressed() const {
    return isClicked;
}

std::string UIManager::getText() const {
    return text.getString();
}