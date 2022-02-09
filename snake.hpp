#pragma once
#include <SDL2/SDL.h>
#include "graphics.hpp"
#include "objects.hpp"

class Application{
public:
    Application();
    ~Application();
    void appLoop();
    void appInit();
private:
    MainWindow* main_window;
    SDL_Renderer* renderer;
    Playground* Room;
    SDL_Event event; // Bind keyboard/mouse events
    Snake* Nico;
    Fruit* Apple;
    Uint32 frame_rate;
    Uint32 snake_rate;
    int dir = 0; // Snake next direction
    int count = 0; // How many cases the snake has moved forward
    void drawNumber(int number, int x, int y);
    void drawDigit(int digit, int xp, int xy);
};

