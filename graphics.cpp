#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "defines.h"

#include "snake.hpp"
#include "objects.hpp"
#include "graphics.hpp"
//#include "score.hpp"

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
  if (SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer) < 0) {
    printf("Erreur lors de la creation d'un renderer : %s\n", SDL_GetError());
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
  rect.x = (rect.x + 1) * TILE_SIZE;
  rect.y = (rect.y + 1) * TILE_SIZE;
  rect.w = TILE_SIZE;
  rect.h = TILE_SIZE;
  SDL_SetRenderDrawColor(renderer, r, g, b, 255);
  SDL_RenderFillRect(renderer, &rect);
}

void printImgOnRenderer(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect pos, int angle) {
  pos.x = (pos.x + 1) * TILE_SIZE;
  pos.y = (pos.y + 1) * TILE_SIZE;
  pos.w = TILE_SIZE;
  pos.h = TILE_SIZE;
  SDL_RenderCopyEx(renderer, texture, NULL, &pos, angle, NULL, SDL_FLIP_NONE);
}

SDL_Texture* loadSDLImg(const char* file, SDL_Renderer* renderer) {
  SDL_Surface* img = IMG_Load(file);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img);
  SDL_FreeSurface(img);
  return texture;
}


Playground::Playground(SDL_Renderer* newRenderer) {
  this-> renderer = newRenderer;
  eraseAndWalls();
}

Playground::~Playground() {}

void Playground::eraseAndWalls() {
  rendererReset(this-> renderer); // Clear the window
  SDL_SetRenderDrawColor(this-> renderer, 20, WALL_COLOR);
  for (int i = 0; i < TILE_SIZE-1; i++) {
    SDL_Rect rect = {i, i, TILE_SIZE*(3+GRID_WIDTH)-(i-1)*2, TILE_SIZE*(3+GRID_HEIGHT)-(i-1)*2};
    SDL_RenderDrawRect(this-> renderer, &rect);
  }
}
