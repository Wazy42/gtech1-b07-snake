#include "objects.hpp"

#ifndef includes
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#define TILE_SIZE 16
#endif

Snake::Snake() {
  this-> dirX = 1;
  this-> dirY = 0;
  this-> x = 1;
  this-> y = 1;
}

Snake::~Snake() {};

void Snake::changeDir(int dir) {
  dirX = (1-dir%2)*(1-dir);
  dirY = (dir%2)*(dir-2);
}

void Snake::move(int dir) {
  if (dir != -1) changeDir(dir);
  this-> x = x + dirX * TILE_SIZE;
  this-> y = y + dirY * TILE_SIZE;
}

void Fruit::fruit_init() {
  relocate();
}

void Fruit::relocate() {
  int x = rand() % SCREEN_WIDTH/TILE_SIZE;
  int y = rand() % SCREEN_HEIGHT/TILE_SIZE;
}
