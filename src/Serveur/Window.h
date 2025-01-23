#ifndef WINDOW_H__
#define WINDOW_H__

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Window {
public:

    Window();
    ~Window();

    void Init(int _width, int _height, const std::string& title);

    void Draw(sf::RenderWindow& _window); // Dessine les éléments du niveau

    //void DisplayPlayerHP(sf::RenderWindow& _Window, int _HpPlayer);
    //void LeaderBoard(sf::RenderWindow& _Window, int _Score);// Gère les événements de la fenêtre

    int Get_FinalScore();

    sf::RenderWindow& getRenderWindow();           // Accède à l'objet SFML RenderWindow

private:
    sf::RenderWindow mwindow;                     // Objet SFML pour la gestion de la fenêtre
};

#endif
