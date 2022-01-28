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

class Fragment {
public:
  int x;  // Position horizontale
  int y; // Position verticale
  Fragment(int newX, int newY);
  ~Fragment();
  void move(int newX, int newY);
  void createFragment(int newX, int newY);
  void printAndNext(SDL_Renderer* renderer);
  Fragment* next; // Next fragment
private:
};

class Fruit {
public:
  Fruit();
  ~Fruit();
  int x;
  int y;
  void relocate();
  void print(SDL_Renderer* renderer);
private:
};


class Snake {
public:
  Snake(int newX, int newY, int dir = 0);
  ~Snake();
  void changeDir(int dir);
  void move(int dir);
  void eat(Fruit* whatever);
  void printEntireSnake(SDL_Renderer* renderer);
  Fragment* Head;
private:
  Fragment* Tail;
  int lastX;
  int lastY;
  int dirX; // Direction horizonale
  int dirY; // Direction vertiacale
  int actualLenght;
};