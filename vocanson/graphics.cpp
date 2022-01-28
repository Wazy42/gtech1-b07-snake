#include "graphics.hpp"

MainWindow::MainWindow() {
  this-> window = NULL; // Affichage fenêtre
  this-> renderer = NULL; // Surface fenêtre
}

MainWindow::~MainWindow() {
  SDL_DestroyRenderer(renderer); // Destruction renderer
  SDL_DestroyWindow(window); // Destruction fenêtre
}

void MainWindow::init(const char *name, int width, int height) {
  // Init window & randerer
  if (SDL_CreateWindowAndRenderer(1600, 900, SDL_WINDOW_RESIZABLE, &window, &renderer) < 0) {
    printf("Erreur lors de la creation d'un renderer : %s", SDL_GetError());
    return;
  }
  SDL_SetWindowTitle(window, name);
}

SDL_Renderer *MainWindow::getRenderer() {
    return this-> renderer;
}

SDL_Window *MainWindow::getWindow() {
    return this-> window;
}
