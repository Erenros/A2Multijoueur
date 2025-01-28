#include "pch.h"
#include "UIManager.h"

UIManager::UIManager() : bIsHovered(false), bIsClicked(false) {}

UIManager::~UIManager() {}

void UIManager::Init(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& buttonText, const sf::Font& font) {
    // Initialisation de la forme du bouton
    mShape.setSize(size);
    mShape.setPosition(position);
    mShape.setFillColor(sf::Color::Blue);  // Couleur par d?faut, ? personnaliser

    // Initialisation du texte du bouton
    mText.setFont(font);
    mText.setString(buttonText);
    mText.setCharacterSize(24);
    mText.setFillColor(sf::Color::White);

    // Centrer le texte sur le bouton
    sf::FloatRect textBounds = mText.getLocalBounds();
    mText.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    mText.setPosition(position.x + size.x / 2, position.y + size.y / 2);
}

void UIManager::Uninit() {
    // Aucune ressource dynamique ? lib?rer dans cet exemple
}

void UIManager::Draw(sf::RenderWindow& window) {
    // Dessiner le bouton et son texte
    window.draw(mShape);
    window.draw(mText);
}

void UIManager::Update(const sf::Vector2i& mousePos, bool isMousePressed) {
    // V?rifier si la souris est sur le bouton
    bIsHovered = mShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));

    // Si le bouton est survol?, changer de couleur
    if (bIsHovered) {
        mShape.setFillColor(sf::Color::Green);  // Couleur lorsque la souris survole
    }
    else {
        mShape.setFillColor(sf::Color::Blue);   // Couleur par d?faut
    }

    // V?rifier si la souris est cliqu?e
    if (bIsHovered && isMousePressed) {
        bIsClicked = true;  // Bouton cliqu?
    }
}

bool UIManager::isPressed() const {
    return bIsClicked;
}

std::string UIManager::getText() const {
    return mText.getString();
}