#ifndef includes
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#define TILE_SIZE 16
#endif

class MainWindow {
public:
  MainWindow();
  ~MainWindow();
  void init(const char *name, int width, int height);
  SDL_Window *getWindow();
  SDL_Renderer *getRenderer();
private:
  SDL_Window *window;
  SDL_Renderer *renderer;
};