class MainWindow {
public:
  MainWindow();
  ~MainWindow();
  void init(const char *name, int width, int height);
  SDL_Window *getWindow();
  SDL_Renderer *getRenderer();
private:
  SDL_Window *window;
  SDL_Renderer *renderer;
};