#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 672
#define TILE_SIZE 32
#define GRID_WIDTH 37
#define GRID_HEIGHT 18

#define BG_COLOR 0, 0, 0
#define SNAKE_COLOR 255, 30, 60
#define FRUIT_COLOR 0, 140, 140
#define WALL_COLOR 40, 200, 40

#define FRUIT_APPLE 0
#define FRUIT_JAM 1
#define FRUIT_SHIELD 2

#include "snake.hpp"
#include "objects.hpp"
#include "graphics.hpp"
//#include "score.hpp"

// Class FRAGMENT
Fragment::Fragment(int newX, int newY, SDL_Renderer* newRenderer) {
  this-> x = newX;
  this-> y = newY;
  this-> next = NULL;
  this-> renderer = newRenderer;
  this-> headTexture = loadSDLImg("sprites/head_c.png", this-> renderer);
  this-> bodyTexture = loadSDLImg("sprites/body_c.png", this-> renderer);
  this-> L_bodyTexture = loadSDLImg("sprites/L_body_c.png", this-> renderer);
  this-> tailTexture = loadSDLImg("sprites/tail_c.png", this-> renderer);
}
Fragment::~Fragment() {
  SDL_DestroyTexture(this-> headTexture);
  SDL_DestroyTexture(this-> bodyTexture);
  SDL_DestroyTexture(this-> L_bodyTexture);
  SDL_DestroyTexture(this-> tailTexture);
  if (next != NULL) delete next;
}

void Fragment::createFragment(int newX, int newY) {
  if (next != NULL) next-> createFragment(newX, newY);
  else this-> next = new Fragment(newX, newY, this->renderer);
}

void Fragment::printAndNext(int angle) {
  if (next != NULL) {
    // formule compliquée pour avoir le prochain angle en fonction des coordonnées
    int nextAngle = 90*((this->x-this->next->x-1)*(this->x-this->next->x)+this->y-this->next->y);
    if (this->x==this->next->x && this->y==this->next->y)
      this-> next-> printAndNext(angle);
    else if (nextAngle != angle) {
      if ((nextAngle+360)%360 - angle == 90) angle -= 90;
      printImgOnRenderer(this-> L_bodyTexture, this->renderer, {this->x, this->y}, angle);
      this-> next-> printAndNext(nextAngle);
    } else {
      printImgOnRenderer(this-> bodyTexture,this->renderer, {this->x, this->y}, angle);
      this-> next-> printAndNext(nextAngle);
    }
  } else {
    printImgOnRenderer(this-> tailTexture, this-> renderer, {this->x, this->y}, angle);
  }
}

void Fragment::printHeadSkin(int angle) {
  printImgOnRenderer(this-> headTexture, this-> renderer, {this->x, this->y}, angle);
}

void Fragment::move(int newX, int newY) {
  if (this-> next != NULL) {
    if (this-> x == this-> next-> x && this-> y == this-> next-> y);
    else next-> move(this-> x, this-> y);
  }
  this-> x = newX;
  this-> y = newY;
}

bool Fragment::checkCollision(int newX, int newY) {
  if (this-> x == newX && this-> y == newY) return true;
  if (this-> next != NULL) return this-> next-> checkCollision(newX, newY);
  return false;
}


// Class FRUIT
Fruit::Fruit(SDL_Renderer* renderer) {
  this-> appleTexture = loadSDLImg("sprites/apple.png", renderer);
  this-> jamTexture = loadSDLImg("sprites/jam.png", renderer);
  this-> shieldTexture = loadSDLImg("sprites/shield.png", renderer);
  relocate();
}

Fruit::~Fruit() {
  SDL_DestroyTexture(this-> appleTexture);
  SDL_DestroyTexture(this-> jamTexture);
  SDL_DestroyTexture(this-> shieldTexture);
}

void Fruit::relocate() {
  this-> x = rand() % GRID_WIDTH;
  this-> y = rand() % GRID_HEIGHT;
  if (rand()%10 == 0) this-> type = FRUIT_SHIELD;
  else if (rand()%5 == 0) this-> type = FRUIT_JAM;
  else this-> type = FRUIT_APPLE;
}

void Fruit::print(SDL_Renderer* renderer) {
  if (this-> type == FRUIT_APPLE)
    printImgOnRenderer(this-> appleTexture, renderer, {this->x, this->y});
  else if (this-> type == FRUIT_JAM)
    printImgOnRenderer(this-> jamTexture, renderer, {this->x, this->y});
  else
    printImgOnRenderer(this-> shieldTexture, renderer, {this->x, this->y});
  
}
 

// Class SNAKE
Snake::Snake(int newX, int newY, int dir, SDL_Renderer* newRenderer) {
  changeDir(dir);
  this-> renderer = newRenderer;
  this-> Head = new Fragment(newX, newY, this-> renderer);
  this-> Head-> createFragment(newX - this-> dirX, newY - this-> dirY);
  this-> Tail = Head-> next;
  this-> actualLenght = 2;
}

Snake::~Snake() {
  delete this-> Head;
}

void Snake::changeDir(int dir) {
  dirX = (1-dir%2)*(1-dir);
  dirY = -(dir%2)*(dir-2);
}

void Snake::move(int dir) {
  changeDir(dir);
  this-> Head-> move(this-> Head->x + this-> dirX, this-> Head->y + this-> dirY);
}

void Snake::eat(Fruit* whatever) {
  int size_gain = 1;
  if (whatever-> type == FRUIT_JAM) {
    size_gain = 3;
  }
  whatever-> relocate();
  for (int i = 0; i < size_gain; i++) {
    this-> Head-> createFragment(this-> Tail-> x, this-> Tail-> y);
    this-> Tail = this-> Tail -> next;
    this-> actualLenght++;
  }
}

void Snake::printEntireSnake() {
  this-> Head -> next-> printAndNext(90*((this->Head->x-this->Head->next->x-1)*(this->Head->x-this->Head->next->x)+this->Head->y-this->Head->next->y));
  this-> Head -> printHeadSkin(90*((dirX-1)*dirX+dirY));
}

bool Snake::hitAWallOrHimself() {
  return this-> Head-> next-> checkCollision(this-> Head-> x, this-> Head->y)
        || this-> Head-> x > GRID_WIDTH || this-> Head-> x < 0
        || this-> Head-> y > GRID_HEIGHT || this-> Head-> y < 0;
}
