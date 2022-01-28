class Snake {
public:
  int x;  // Position horizontale
  int y; // Position verticale
  Snake();
  ~Snake();
  void changeDir(int num);
  void move();
private:
  int dirX; // Direction horizonale
  int dirY; // Direction vertiacale
};

class Fruit {
public:
  int x;
  int y;
  void fruit_init();
  void relocate();
private:
};