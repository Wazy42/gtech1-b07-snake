#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "graphics.cpp"
#include "objects.cpp"
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#define GRID_WIDTH 1040
#define GRID_HEIGHT 800
#define SCORE_HEIGHT 700
#define TILE_SIZE 16


void main(int argc, char *argv[]) {
  // SDL Init
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Erreur d'initialisation de la SDL : %s",SDL_GetError());//on affiche l'erreur
    return; //on sort du programme pour éviter de plus gros problèmes
  }
  
  MainWindow main_window;
  main_window.init("First window", 1600, 900);
  SDL_Window *window = main_window.getWindow();
  SDL_Renderer *renderer = main_window.getRenderer();
  SDL_Surface *screenSurface = SDL_GetWindowSurface(window);

  SDL_Event event;
  Snake *Head = new Snake();
  Uint32 frame_rate = 60;

  while (1) {
    Uint32 frame_time_start = SDL_GetTicks();
    // Events
    SDL_PollEvent(&event);
    
    switch (event.type) {
      case SDL_QUIT:
        SDL_Quit();
        return;
      case SDL_KEYDOWN:
        switch(event.key.keysym.sym) {
          case SDLK_UP:
            CARRE-> changeDir(1);
            break;
          case SDLK_DOWN:
            CARRE-> changeDir(3);
            break;
          case SDLK_LEFT:
            CARRE-> changeDir(2);
            break;
          case SDLK_RIGHT:
            CARRE-> changeDir(0);
            break;
        }
    }
    Head-> move();

    // Drawing
    SDL_FillRect(screenSurface, NULL, 0);
    SDL_Rect rect = {CARRE->x, CARRE->y, 16, 16};
    SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface-> format, 255, 0, 0));

    // Update
    SDL_UpdateWindowSurface(main_window.getWindow());
    SDL_Delay(SDL_GetTicks() - frame_time_start);
  }
}