#include "graphics.hpp"

#ifndef includes
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 675
#define TILE_SIZE 16
#define GRID_WIDTH SCREEN_WIDTH/TILE_SIZE
#define GRID_HEIGHT SCREEN_HEIGHT/TILE_SIZE
#endif

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
  if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer) < 0) {
    printf("Erreur lors de la creation d'un renderer : %s", SDL_GetError());
    return;
  }
  SDL_SetWindowTitle(window, name);
}

SDL_Renderer *MainWindow::getRenderer() {
    return this-> renderer;
}

void rendererReset(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void printRectOnRenderer(SDL_Rect rect, SDL_Renderer* renderer, int r, int g, int b) {
  rect.x = rect.x * TILE_SIZE;
  rect.y = rect.y * TILE_SIZE;
  rect.w = TILE_SIZE;
  rect.h = TILE_SIZE;
  SDL_SetRenderDrawColor(renderer, r, g, b, 255);
  SDL_RenderFillRect(renderer, &rect);
}
