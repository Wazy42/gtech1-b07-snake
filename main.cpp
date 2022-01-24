#include "snake.cpp"

Game *game = nullptr;

int main(int argc, const char * argv[]){

    game = new Game();

    game->init("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, true);

    while(game->running()){

        game->handleEvents();
        game->update();
        game->render();

    }

    game->clean();

    return 0;
}