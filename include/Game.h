#pragma once
#include "Entity.h"
#include "Player.h"
#include "Window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

struct Keys {
  bool left = false;
  bool right = false;
  bool space = false;
};

class Game {
public:
  void eventHandler(SDL_Event &event, Keys *ks);
  void initGame();
  void play();
  void update(Keys &ks);
  void render();
  void endGame();

private:
  bool isPlay = true;
  int tempCounter = 0;
  Window *window = new Window();
  Player plr;
  SDL_Texture *texture;
  std::vector<Entity> tiles;
};
