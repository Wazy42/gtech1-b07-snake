#include "objects.hpp"

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

void Snake::move() {
  this-> x = x + dirX;
  this-> y = y + dirY;
}

void Fruit::fruit_init() {
  relocate();
}

void Fruit::relocate() {
  int x = rand() % GRID_WIDTH;
  int y = rand() % GRID_HEIGHT;
}
