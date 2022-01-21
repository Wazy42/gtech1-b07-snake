#ifndef snake_cpp
#define snake_cpp

#include <SDL2/SDL.h>

class MainWindow {
public:
  MainWindow();
  ~MainWindow();
  int init(int width, int height);
  SDL_Renderer *getRenderer();
private:
  SDL_Window *window;
  SDL_Renderer *renderer;
};

#endif