#ifndef snake_cpp
#define snake_cpp

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1600
#define TILE_SIZE 20

class MainWindow {
public:
  MainWindow();
  ~MainWindow();
  int init(const char *name, int width, int height);
  SDL_Window *getWindow();
  SDL_Renderer *getRenderer();
  
private:
  SDL_Window *window;
  SDL_Renderer *renderer;
};

class Square {
public:
  int x;  // Position horizontale
  int y; // Position verticale
  Square();
  ~Square();
  int changeDir(int num);
  int move();

private:
  int dirX; // Direction horizonale
  int dirY; // Direction vertiacale
  
  Segment* head;
};

class Segment{
  public:
    int head();
    int heatx;
    int heady;

  private:
    Segment* next;
};

class Fruit{
  public:
    int fruitx;
    int fruity;
    void fruit_init();
    void fruit_rand();

  private:

};


#endif