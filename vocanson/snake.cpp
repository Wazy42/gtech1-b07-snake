#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "snake.hpp"

MainWindow::MainWindow() {
  this-> window = NULL; // Affichage fenêtre
  this-> renderer = NULL; // Surface fenêtre
}

MainWindow::~MainWindow() {
  SDL_DestroyRenderer(renderer); // Destruction renderer
  SDL_DestroyWindow(window); // Destruction fenêtre
}

int MainWindow::init(const char *name, int width, int height) {
  // Init window & randerer
  if (SDL_CreateWindowAndRenderer(1600, 900, SDL_WINDOW_RESIZABLE, &window, &renderer) < 0) {
    printf("Erreur lors de la creation d'un renderer : %s", SDL_GetError());
    return EXIT_FAILURE;
  }
  SDL_SetWindowTitle(window, name);
  return EXIT_SUCCESS;
}
SDL_Renderer *MainWindow::getRenderer() {
    return this-> renderer;
}

SDL_Window *MainWindow::getWindow() {
    return this-> window;
}


Square::Square() {
  this-> dirX = 1;
  this-> dirY = 0;
  this-> x = 1;
  this-> y = 1;
}

Square::~Square() {};

int Square::changeDir(int num) {
  // Go UP
  if (num == 1 && dirY != 1) {
    this-> dirX = 0;
    this-> dirY = -1;
    return EXIT_SUCCESS;
  }
  // Go DOWN
  if (num == 3 && dirY != -1) {
    this-> dirX = 0;
    this-> dirY = 1;
    return EXIT_SUCCESS;
  }
  // Go LEFT
  if (num == 2 && dirX != 1) {
    this-> dirX = -1;
    this-> dirY = 0;
    return EXIT_SUCCESS;
  }
  // Go RIGHT
  if (num == 0 && dirX != -1) {
    this-> dirX = 1;
    this-> dirY = 0;
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int Square::move() {
  this-> x = x + dirX;
  this-> y = y + dirY;
  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  // SDL Init
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Erreur d'initialisation de la SDL : %s",SDL_GetError());//on affiche l'erreur
    return EXIT_FAILURE;//on sort du programme pour éviter de plus gros problèmes
  }
  
  MainWindow main_window;
  main_window.init("First window", 1600, 900);
  SDL_Window *window = main_window.getWindow();
  SDL_Renderer *renderer = main_window.getRenderer();
  SDL_Surface *screenSurface = SDL_GetWindowSurface(window);

  SDL_Event event;
  Square *CARRE = new Square();
  Uint32 frame_rate = 60;

  while (1) {
    Uint32 frame_time_start = SDL_GetTicks();
    // Events
    SDL_PollEvent(&event);
    
    switch (event.type) {
      case SDL_QUIT:
        SDL_Quit();
        return 0;
      case SDL_KEYDOWN:
        switch(event.key.keysym.sym) {
          case SDLK_UP:
            CARRE-> changeDir(1);
            break;
          case SDLK_DOWN:
            CARRE-> changeDir(3);
            break;
          case SDLK_LEFT:
            CARRE-> changeDir(2);
            break;
          case SDLK_RIGHT:
            CARRE-> changeDir(0);
            break;
        }
    }
    CARRE-> move();

    // Drawing
    SDL_FillRect(screenSurface, NULL, 0);
    SDL_Rect rect = {CARRE->x, CARRE->y, 16, 16};
    SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface-> format, 255, 0, 0));

    // Update
    SDL_UpdateWindowSurface(main_window.getWindow());
    SDL_Delay(SDL_GetTicks() - frame_time_start);
  }
}