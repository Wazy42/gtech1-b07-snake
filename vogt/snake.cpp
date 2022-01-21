#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    /* Initialisation de la SDL et de la fenêtre de jeu */
    SDL_Window* window = NULL; // Affichage fenêtre
    SDL_Surface* screenSurface = NULL; // Surface fenêtre
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur d'initialisation de la SDL : %s",SDL_GetError()); //on affiche l'erreur
        return EXIT_FAILURE; //On sort du programme pour éviter de plus gros problèmes
    }
    // Init fenêtre
    window = SDL_CreateWindow("Snake!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Impossible de créer la fenêtre: %s\n", SDL_GetError()); //on affiche l'erreur
        return EXIT_FAILURE; //on sort du programme pour éviter de plus gros problèmes
    }

    screenSurface = SDL_GetWindowSurface(window); // Surface de la fenêtre
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF)); 
    SDL_UpdateWindowSurface(window); // Mise à jour fenêtre

    // Ligne temporaire, garde l'afficage de la fenetre pendant 2 sec avant le destroy
    SDL_Delay( 2000 );

    // game_init();
    // game_loop();

    SDL_DestroyWindow(window); // Destruction fenêtre
    SDL_Quit(); // On quitte la SDL
    
    return 0;
}

int game_init() {
    return 0;
}

int game_loop() {
    return 0;
}

class Snake {
    /* Morceau de serpent */
public:
    Snake(int newx, int newy, int newHeading) { // Consructeur
        this-> x = newx;
        this-> y = newy;
        this-> heading = newHeading;
        this-> nextSnake = NULL;
    }

    ~Snake() { // Destructeur
        if (nextSnake != NULL) {
            delete nextSnake;
        }
    }

    int move(int newx, int newy) { // Modification des coordonnées
        if (nextSnake != NULL) {
            nextSnake-> move(x, y);
        }
        this-> x = newx;
        this-> y = newy;
        return 0;
    }

    int turn(int degree) { // Modification de l'orientation 0 = est
        this-> heading = degree;
        return 0;
    }

    int addSnake() { // Ajoute un segment de serpent
        if (nextSnake != NULL) {
            nextSnake-> addSnake();
        } else {
            this-> nextSnake = new Snake(x, y, heading);
        }
    }

private:
    int x; // coordonnées
    int y; // coordonnées
    int heading; // Orientation du morceau
    Snake *nextSnake; // Prochain morceau de serpent
};

class Field {
    /* Zone du jeu */
    public:
        int width;
        int height;
        
        Field() {
            this -> width = 1600;
            this -> height = 900;
        }

        Draw(){
            for (x = 0; x < height; x++){
                for (y = 0; y < width; y++){
                    if (x == 0 || x == width) - 1 || y == 0 || y == height - 1){
                        printf("#");
                    }
                    else{
                        printf(" ");
                    }
                }
                printf("\n");
            }
        }
    private:
    };


class Fruit{

    public: Fruit(int posx, int posy, int fruit, int skin)
             : x( posx ), y( posy )
        {
            fruit = rand() % skin;
            fruit = rand() % Field.width;
            fruit = rand() % Field.height;

            this -> x = posx;
            this -> y = posy;
            this -> skin[2] = skin;


        }


    private:
        int x, y;
        char skin[2];

 };