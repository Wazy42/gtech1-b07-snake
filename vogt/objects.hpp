#ifndef includes
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#define TILE_SIZE 16
#endif

class Snake {
public:
  int x;  // Position horizontale
  int y; // Position verticale
  Snake();
  ~Snake();
  void changeDir(int dir);
  void move(int dir = -1);
private:
  int dirX; // Direction horizonale
  int dirY; // Direction vertiacale
};

class Fruit {
public:
  int x;
  int y;
  void fruit_init();
  void relocate();
private:
};