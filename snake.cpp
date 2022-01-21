#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "snake.hpp"

MainWindow::MainWindow() {
    this-> window = NULL; // Affichage fenêtre
    this-> renderer = NULL; // Surface fenêtre
}
MainWindow::~MainWindow() {
    SDL_DestroyWindow(window); // Destruction fenêtre
}
int MainWindow::init(int width, int height) {
    // Init fenêtre
    window = SDL_CreateWindow("Snake!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Impossible de créer la fenêtre: %s\n", SDL_GetError()); //on affiche l'erreur
        return EXIT_FAILURE; //on sort du programme pour éviter de plus gros problèmes
    }
    return 0;
}
SDL_Renderer *MainWindow::getRenderer() {
    return this-> renderer;
}
