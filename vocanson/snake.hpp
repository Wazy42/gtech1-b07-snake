#ifndef snake_cpp
#define snake_cpp

#include <SDL2/SDL.h>

class MainWindow {
public:
  MainWindow();
  ~MainWindow();
  int init(const char *name, int width, int height);
  SDL_Window *getWindow();
  SDL_Renderer *getRenderer();
private:
  SDL_Window *window;
  SDL_Renderer *renderer;
};

class Square {
public:
  int x;  // Position horizontale
  int y; // Position verticale
  Square();
  ~Square();
  int changeDir(int num);
  int move();
private:
  int dirX; // Direction horizonale
  int dirY; // Direction vertiacale
};

#endif