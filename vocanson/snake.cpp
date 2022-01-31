#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 1260
#define SCREEN_HEIGHT 672
#define TILE_SIZE 32
#define GRID_WIDTH 36
#define GRID_HEIGHT 18

#define BG_COLOR 0, 0, 0
#define SNAKE_COLOR 255, 30, 60
#define FRUIT_COLOR 0, 140, 140
#define WALL_COLOR 40, 200, 40

#define SIZE_GAIN_BY_EATING 3

#include "graphics.cpp"
#include "objects.cpp"

int main(int argc, char *argv[]) {
  /// Graphical init
  if(SDL_Init(SDL_INIT_VIDEO) < 0) { // SDL init error ?
    printf("SDL initialization error: %s\nn",SDL_GetError()); // Print error
    return 1; // Quit to avoid more problems
  }
  IMG_Init(IMG_INIT_PNG);
  MainWindow main_window; // Creating window
  main_window.init("Snake, the game.", SCREEN_WIDTH, SCREEN_HEIGHT);
  SDL_Renderer *renderer = main_window.getRenderer(); // Get renderer
  Playground Room(renderer);
  
  /// Variables init
  SDL_Event event; // Bind keyboard/mouse events
  srand(time(0)); // rand() init
  Snake *Nico = new Snake(GRID_WIDTH/3, GRID_HEIGHT/2, 0); // Snake
  Fruit *Apple = new Fruit(); // Fruit
  Uint32 frame_rate = 9; // Frame rate (fps)
  int dir = 0; // Snake next direction
  int count = 0; // How many cases the snake has moved forward

  /// Main loop
  do {
    count++; 
    Uint32 tTime = SDL_GetTicks(); // For frame rate
    
    /// Events
    int lastDir = dir; // Last direction (we can't go backward)
    while (SDL_PollEvent(&event)) { // While there is keyboard/mouse event in the queue
      switch (event.type) {
        case SDL_QUIT: // In case we hit the red X or Alt+f4
          delete Nico;
          IMG_Quit();
          SDL_Quit();
          return 0;
        case SDL_KEYDOWN: // We pressed a key on the keyboard
          if (event.key.keysym.sym == SDLK_UP && lastDir != 1) dir = 3; // Up arrow
          if (event.key.keysym.sym == SDLK_DOWN && lastDir != 3) dir = 1; // Down arrow
          if (event.key.keysym.sym == SDLK_LEFT && lastDir != 0) dir = 2; // Left arrow
          if (event.key.keysym.sym == SDLK_RIGHT && lastDir != 2) dir = 0; // Right arrow
      }
    }
    Nico-> move(dir); // Snake moves forward
    // If the head is on a fruit, we eat it
    if (Apple->x == Nico->Head->x && Apple->y == Nico->Head->y) Nico->eat(Apple);
    
    /// Drawing
    Room.eraseAndWalls();
    Nico-> printEntireSnake(renderer); // Display snake
    Apple-> print(renderer); // Display fruit
    SDL_RenderPresent(renderer); // Update the window (print all at once)

    /// Frame rate
    tTime = SDL_GetTicks() - tTime; // tTime is now time elapsed in execution
    // If execution time is less than the frame rate (no lag), we wait next frame
    if (1000 / frame_rate - tTime > 0) SDL_Delay(1000 / frame_rate - tTime);
  } while (!Nico-> hitAWallOrHimself());
  SDL_Delay(1000);
  delete Nico;
  IMG_Quit();
  SDL_Quit();
}