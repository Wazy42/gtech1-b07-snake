#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 672
#define TILE_SIZE 32
#define GRID_WIDTH 37
#define GRID_HEIGHT 18

#define BG_COLOR 0, 0, 0
#define SNAKE_COLOR 255, 30, 60
#define FRUIT_COLOR 0, 140, 140
#define WALL_COLOR 40, 200, 40

#define SIZE_GAIN_BY_EATING 3

#include "snake.hpp"
#include "objects.hpp"
#include "graphics.hpp"
//#include "score.hpp"

int main() {
  Application app;
  app.appInit();
  app.appLoop();
  return 0;
}