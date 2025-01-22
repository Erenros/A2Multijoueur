#include "pch.h"
#include "Window.h"

Window::Window() 
{
}

Window::~Window() 
{
}

void Window::Init(int _width, int _height, const std::string& title) {
    m_window.create(sf::VideoMode(_width, _height), title);
    if (!m_window.isOpen()) {
        std::cerr << "Erreur de création de la fenêtre!" << std::endl;
    }
}

void Window::Draw(sf::RenderWindow& _window) {
    _window.clear();
    _window.display();
}

//void Window::DisplayPlayerHP(sf::RenderWindow& _Window, int _HpPlayer) {
//    // Exemple pour afficher la barre de vie (à adapter avec SFML)
//    sf::RectangleShape hpBar(sf::Vector2f(200.0f, 20.0f));
//    hpBar.setFillColor(sf::Color::Green);
//    hpBar.setSize(sf::Vector2f(_HpPlayer * 2, 20));  // Exemple de taille proportionnelle à la vie
//    _Window.draw(hpBar);
//}

//void Window::LeaderBoard(sf::RenderWindow& _Window, int _Score) {
//    // Affiche le score en haut de l'écran
//    sf::Font font;
//    if (!font.loadFromFile("path/to/font.ttf")) {
//        std::cerr << "Erreur de chargement de la police!" << std::endl;
//    }
//
//    sf::Text scoreText;
//    scoreText.setFont(font);
//    scoreText.setString("Score: " + std::to_string(_Score));
//    scoreText.setCharacterSize(24);
//    scoreText.setFillColor(sf::Color::White);
//    _Window.draw(scoreText);
//}

int Window::Get_FinalScore() {
    return 0;
}

sf::RenderWindow& Window::getRenderWindow() {
    return m_window;
}

