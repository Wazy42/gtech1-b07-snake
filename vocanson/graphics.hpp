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

class MainWindow {
public:
  MainWindow();
  ~MainWindow();
  void init(const char *name, int width, int height);
  SDL_Renderer *getRenderer();
private:
  SDL_Window *window;
  SDL_Renderer *renderer;
};

void rendererReset(SDL_Renderer* renderer);

void printRectOnRenderer(SDL_Rect rect, SDL_Renderer* renderer, int r, int g, int b);
