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

#include "graphics.cpp"
#include "objects.cpp"

int main(int argc, char *argv[]) {
  /// SDL init
  if(SDL_Init(SDL_INIT_VIDEO) < 0) { // Error ?
    printf("SDL initialization error: %s",SDL_GetError()); // Print error
    return 1; // Quit to avoid more problems
  }
  
  /// Variables init
  MainWindow main_window; // Creating window
  main_window.init("Snake, the game.", SCREEN_WIDTH, SCREEN_HEIGHT);
  SDL_Renderer *renderer = main_window.getRenderer(); // Get renderer

  SDL_Event event; // Bind keyboard/mouse events
  Snake *Nico = new Snake(0, 0, 0); // Snake
  Fruit *Apple = new Fruit(); // Fruit
  Uint32 frame_rate = 10; // Frame rate (fps)
  int dir = 0; // Snake next direction
  int count = 0; // How many cases the snake has moved forward

  /// Main loop
  while (1) {
    count++; 
    Uint32 tTime = SDL_GetTicks(); // For frame rate
    
    /// Events
    int lastDir = dir; // Last direction (we can't go backward)
    while (SDL_PollEvent(&event)) { // While there is keyboard/mouse event in the queue
      switch (event.type) {
        case SDL_QUIT: // In case we hit the red X or Alt+f4
          delete Nico;
          SDL_Quit();
          return 0;
        case SDL_KEYDOWN: // We pressed a key on the keyboard
          if (event.key.keysym.sym == SDLK_UP && lastDir != 3) dir = 1; // Up arrow
          if (event.key.keysym.sym == SDLK_DOWN && lastDir != 1) dir = 3; // Down arrow
          if (event.key.keysym.sym == SDLK_LEFT && lastDir != 0) dir = 2; // Left arrow
          if (event.key.keysym.sym == SDLK_RIGHT && lastDir != 2) dir = 0; // Right arrow
      }
    }
    // If the head is on a fruit, we eat it
    if (Apple->x == Nico->Head->x && Apple->y == Nico->Head->y) Nico->eat(Apple);
    Nico-> move(dir); // Snake moves forward
    
    /// Drawing
    rendererReset(renderer); // Clear the window
    Nico-> printEntireSnake(renderer); // Display snake
    Apple-> print(renderer); // Display fruit

    /// Update
    tTime = SDL_GetTicks() - tTime; // tTime is now time elapsed in execution
    // If execution time is less than the frame rate (no lag), we wait next frame
    if (1000 / frame_rate - tTime > 0) SDL_Delay(1000 / frame_rate - tTime);
    SDL_RenderPresent(renderer); // Update the window (print all at once)
  }
}