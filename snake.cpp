#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "score.hpp"

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


Application::Application(){
  if(SDL_Init(SDL_INIT_VIDEO) < 0) { // SDL init error ?
    printf("SDL initialization error: %s\nn",SDL_GetError()); // Print error
    return 1; // Quit to avoid more problems
  IMG_Init(IMG_INIT_PNG);
  srand(time(0)); // rand() init
  this-> frame_rate = 30; // Frame rate (fps)
  this-> snake_rate = 8 // Tiles per second (tps)
  appInit();
  appLoop();
}

Application::~Application(){
  delete this-> Nico;
  delete this-> Apple;
  IMG_Quit();
  SDL_Quit();
}

void Application::appLoop() {
  /// Main loop
  do {
    count++; 
    Uint32 tTime = SDL_GetTicks(); // For frame rate
    
    /// Events
    int lastDir = this-> dir; // Last direction (we can't go backward)
    while (SDL_PollEvent(this-> &event)) { // While there is keyboard/mouse event in the queue
      switch (this-> event.type) {
        case SDL_QUIT: // In case we hit the red X or Alt+f4
          ~Application()
        case SDL_KEYDOWN: // We pressed a key on the keyboard
          if (this-> event.key.keysym.sym == SDLK_UP && lastDir != 1) dir = 3; // Up arrow
          if (this-> event.key.keysym.sym == SDLK_DOWN && lastDir != 3) dir = 1; // Down arrow
          if (this-> event.key.keysym.sym == SDLK_LEFT && lastDir != 0) dir = 2; // Left arrow
          if (this-> event.key.keysym.sym == SDLK_RIGHT && lastDir != 2) dir = 0; // Right arrow
      }
    }
    Nico-> move(dir); // Snake moves forward
    // If the head is on a fruit, we eat it
    if (this->Apple->x == this->Nico->Head->x && this->Apple->y == this->Nico->Head->y)
      this-> Nico->eat(this-> Apple);
    
    /// Drawing
    this-> Room.eraseAndWalls();
    this-> Nico-> printEntireSnake(this-> renderer); // Display snake
    this-> Apple-> print(this-> renderer); // Display fruit
    SDL_RenderPresent(this-> renderer); // Update the window (print all at once)

    /// Frame rate
    tTime = SDL_GetTicks() - tTime; // tTime is now time elapsed in execution
    // If execution time is less than the frame rate (no lag), we wait next frame
    if (1000 / this-> frame_rate - tTime > 0) SDL_Delay(1000 / this-> frame_rate - tTime);
  } while (!this-> Nico-> hitAWallOrHimself());
  SDL_Delay(1000);
  delete Nico; 
}

void appInit() {
  }
  /// Graphical init
  this-> main_window.init("ゲームをヘビ", SCREEN_WIDTH, SCREEN_HEIGHT);
  this-> renderer = main_window.getRenderer(); // Get renderer
  this-> Room(renderer);
  
  /// Variables init
  this-> Nico = new Snake(GRID_WIDTH/3, GRID_HEIGHT/2, 0); // Snake
  this-> Apple = new Fruit(); // Fruit
}