#include "objects.hpp"

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

void Fragment::printAndNext(SDL_Renderer* renderer, int angle) {
  if (next != NULL) {
    // formule compliquée pour avoir le prochain angle en fonction des coordonnées
    int nextAngle = 90*((this->x-this->next->x-1)*(this->x-this->next->x)+this->y-this->next->y);
    if (this->x==this->next->x && this->y==this->next->y)
      this-> next-> printAndNext(renderer, angle);
    else if (nextAngle != angle) {
      if ((nextAngle+360)%360 - angle == 90) angle -= 90;
      printImgOnRenderer("../sprites/L_body_c.png", renderer, {this->x, this->y}, angle);
      this-> next-> printAndNext(renderer, nextAngle);
    } else {
      printImgOnRenderer("../sprites/body_c.png", renderer, {this->x, this->y}, angle);
      this-> next-> printAndNext(renderer, nextAngle);
    }
  } else {
    printImgOnRenderer("../sprites/tail_c.png", renderer, {this->x, this->y}, angle);
  }
}

void Fragment::printSingleSkin(const char* file, SDL_Renderer* renderer, int angle) {
  printImgOnRenderer(file, renderer, {this->x, this->y}, angle);
}

void Fragment::move(int newX, int newY) {
  if (this-> next != NULL) {
    if (this-> x == this-> next-> x && this-> y == this-> next-> y);
    else next-> move(this-> x, this-> y);
  }
  this-> x = newX;
  this-> y = newY;
}

bool Fragment::checkColision(int newX, int newY) {
  if (this-> x == newX && this-> y == newY) return true;
  if (this-> next != NULL) return this-> next-> checkColision(newX, newY);
  return false;
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
  printImgOnRenderer("../sprites/apple.png", renderer, {this->x, this->y});
}
 

// Class SNAKE
Snake::Snake(int newX, int newY, int dir) {
  changeDir(dir);
  this-> Head = new Fragment(newX, newY);
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
  whatever-> relocate();
  for (int i = 0; i < SIZE_GAIN_BY_EATING; i++) {
    this-> Head-> createFragment(this-> Tail-> x, this-> Tail-> y);
    this-> Tail = this-> Tail -> next;
    this-> actualLenght++;
  }
}

void Snake::printEntireSnake(SDL_Renderer* renderer) {
  this-> Head -> next-> printAndNext(renderer, 90*((this->Head->x-this->Head->next->x-1)*(this->Head->x-this->Head->next->x)+this->Head->y-this->Head->next->y));
  this-> Head -> printSingleSkin("../sprites/head_c.png", renderer, 90*((dirX-1)*dirX+dirY));
}

bool Snake::hitAWallOrHimself() {
  return this-> Head-> next-> checkColision(this-> Head-> x, this-> Head->y)
        || this-> Head-> x > GRID_WIDTH || this-> Head-> x < 0
        || this-> Head-> y > GRID_HEIGHT || this-> Head-> y < 0;
}
