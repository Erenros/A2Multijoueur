#include "pch.h"
#include "GameManager.h"

int main() {
    GameManager gameManager;

    if (gameManager.Init() != 0) {
        std::cerr << "Erreur lors de l'initialisation du jeu." << std::endl;
        return -1;
    }

    gameManager.GameLoop();

    gameManager.Uninit();

    return 0;
}