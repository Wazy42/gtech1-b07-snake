#ifndef includes
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#define TILE_SIZE 16
#endif

#include "graphics.cpp"
#include "objects.cpp"

int main(int argc, char *argv[]) {
  // SDL Init
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Erreur d'initialisation de la SDL : %s",SDL_GetError());//on affiche l'erreur
    return 1; //on sort du programme pour éviter de plus gros problèmes
  }
  
  MainWindow main_window;
  main_window.init("First window", 1600, 900);
  SDL_Window *window = main_window.getWindow();
  SDL_Renderer *renderer = main_window.getRenderer();
  SDL_Surface *screenSurface = SDL_GetWindowSurface(window);

  SDL_Event event;
  Snake *Head = new Snake();
  Uint32 frame_rate = 10;
  int dir = 0;

  while (1) {
    Uint32 tTime = SDL_GetTicks();
    // Events
    int lastDir = dir;

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          SDL_Quit();
          return 0;
        case SDL_KEYDOWN:
          if (event.key.keysym.sym == SDLK_UP && lastDir != 3)
            dir = 1;
          if (event.key.keysym.sym == SDLK_DOWN && lastDir != 1)
            dir = 3;
          if (event.key.keysym.sym == SDLK_LEFT && lastDir != 0)
            dir = 2;
          if (event.key.keysym.sym == SDLK_RIGHT && lastDir != 2)
            dir = 0;
      }
    }
    Head-> move(dir);

    // Drawing
    SDL_FillRect(screenSurface, NULL, 0);
    SDL_Rect rect = {Head->x, Head->y, 16, 16};
    SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface-> format, 255, 0, 0));

    // Update
    tTime = SDL_GetTicks() - tTime;
      SDL_Delay(1000 / frame_rate - tTime);
    SDL_UpdateWindowSurface(main_window.getWindow());
  }
}