#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "defines.h"

#include "snake.hpp"
#include "objects.hpp"
#include "graphics.hpp"

int main() {
  Application app;
  app.appInit();
  app.appLoop();
  return 0;
}