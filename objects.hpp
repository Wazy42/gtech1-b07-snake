#pragma once

class Fragment {
public:
  int x;  // Position horizontale
  int y; // Position verticale
  Fragment(int newX, int newY);
  ~Fragment();
  void move(int newX, int newY);
  void createFragment(int newX, int newY);
  void printAndNext(SDL_Renderer* renderer, int angle);
  void printSingleSkin(const char* file, SDL_Renderer* renderer, int angle);
  bool checkCollision(int newX, int newY);
  Fragment* next; // Next fragment
private:
};

class Fruit {
public:
  Fruit();
  ~Fruit();
  int x;
  int y;
  void relocate();
  void print(SDL_Renderer* renderer);
private:
};


class Snake {
public:
  Snake(int newX, int newY, int dir = 0);
  ~Snake();
  void changeDir(int dir);
  void move(int dir);
  void eat(Fruit* whatever);
  void printEntireSnake(SDL_Renderer* renderer);
  bool hitAWallOrHimself();
  Fragment* Head;
private:
  Fragment* Tail;
  int dirX; // Direction horizonale
  int dirY; // Direction vertiacale
  int actualLenght;
};