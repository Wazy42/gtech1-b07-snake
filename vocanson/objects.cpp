#include "objects.hpp"

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


// Class FRAGMENT
Fragment::Fragment(int newX, int newY) {
  this-> x = newX;
  this-> y = newY;
  this-> next = NULL;
}
Fragment::~Fragment() {
  if (next != NULL) delete next;
}

void Fragment::createFragment(int newX, int newY) {
  if (next != NULL) next-> createFragment(newX, newY);
  else this-> next = new Fragment(newX, newY);
}

void Fragment::printAndNext(SDL_Renderer* renderer) {
  printRectOnRenderer({this->x, this->y}, renderer, 255, 0, 0);
  if (next != NULL) this-> next-> printAndNext(renderer);
}

void Fragment::move(int newX, int newY) {
  if (next != NULL) next-> move(this-> x, this-> y);
  this-> x = newX;
  this-> y = newY;
}


// Class FRUIT
Fruit::Fruit() {
  relocate();
}

Fruit::~Fruit() {}

void Fruit::relocate() {
  this-> x = rand() % GRID_WIDTH;
  this-> y = rand() % GRID_HEIGHT;
}

void Fruit::print(SDL_Renderer* renderer) {
  printRectOnRenderer({this->x, this->y}, renderer, 0, 255, 0);
}
 

// Class SNAKE
Snake::Snake(int newX, int newY, int dir) {
  changeDir(dir);
  this-> Head = new Fragment(newX, newY);
  this-> Head-> createFragment(newX - this-> dirX, newY - this-> dirY);
  this-> lastX = newX - this-> dirX;
  this-> lastY = newY - this-> dirY;
  this-> Tail = Head-> next;
  this-> actualLenght = 2;
}

Snake::~Snake() {
  delete this-> Head;
}

void Snake::changeDir(int dir) {
  dirX = (1-dir%2)*(1-dir);
  dirY = (dir%2)*(dir-2);
}

void Snake::move(int dir) {
  changeDir(dir);
  this-> Head-> move(this-> Head->x + this-> dirX, this-> Head->y + this-> dirY);
  this-> lastX = this-> Tail-> x;
  this-> lastY = this-> Tail-> y;
}

void Snake::eat(Fruit* whatever) {
  whatever-> relocate();
  this-> Head-> createFragment(lastX, lastY);
  this-> Tail = this-> Tail -> next;
  this-> actualLenght++;
  printf("Snake: %d tiles\n", actualLenght);
}

void Snake::printEntireSnake(SDL_Renderer* renderer) {
  this-> Head -> printAndNext(renderer);
}
