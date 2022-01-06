#include "../include/Game.h"
#include "../include/Player.h"
#include "../include/Utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const std::string LEVELS_DATA = "assets/levels";
const char *GRAPHICS_DATA = "assets/images/graphics.png";

void Game::initGame() {
  if (!(SDL_Init(SDL_INIT_VIDEO)))
    std::cerr << SDL_GetError() << std::endl;
  if (!(IMG_Init(IMG_INIT_PNG)))
    std::cerr << SDL_GetError() << std::endl;
  Game::texture = Game::window->initTexture(GRAPHICS_DATA);
  Game::tiles = util::getLevel(LEVELS_DATA);
}

void Game::play() {
  Keys *ks = new Keys();
  SDL_Event event;
  while (Game::isPlay) {
    while (SDL_PollEvent(&event) > 0) {
      Game::eventHandler(event, ks);
    }
    Game::update(*ks);
    Game::render();
    Game::window->display();
    SDL_Delay(70);
  }
}

void Game::eventHandler(SDL_Event &event, Keys *ks) {
  if (event.type == SDL_KEYUP) {
    switch (event.key.keysym.sym) {
    case SDLK_LEFT:
      ks->left = false;
      break;
    case SDLK_RIGHT:
      ks->right = false;
      break;
    case SDLK_SPACE:
      ks->space = false;
      break;
    }
  }
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
    case SDLK_LEFT:
      ks->left = true;
      break;
    case SDLK_RIGHT:
      ks->right = true;
      break;
    case SDLK_SPACE:
      ks->space = true;
      break;
    case SDLK_q:
      Game::isPlay = false;
      break;
    }
  }
}

void Game::render() {
  Game::window->clear();
  for (Entity &tile : Game::tiles) {
    Game::window->render(tile.getDest(), tile.getSrc(), Game::texture);
  }
  Game::window->render(Game::plr.getDest(), Game::plr.getSrc(), Game::texture);
}

void Game::update(Keys &ks) {
  if (Game::tempCounter % 2 == 0) {
    Game::plr.incSpriteIndex();
  }
  Game::tempCounter++;
  Pos plrPos = Game::plr.getPlrPos();
  Velocity v = plr.getVelocity();
  if (ks.space == true && !Game::plr.isJumping()) {
    Game::plr.setIsJumping(true);
    Game::plr.setIdle(false);
    v.velY = -17;
  }
  if (ks.left) {
    Game::plr.setIdle(false);
    Game::plr.setDirection(false);
    v.velX = -1;
  }
  if (ks.right) {
    Game::plr.setIdle(false);
    Game::plr.setDirection(true);
    v.velX = 1;
  }
  if (!ks.right && !ks.left) {
    Game::plr.setIdle(true);
  }
  if (!Game::plr.isJumping() && !ks.right && !ks.left && v.velX != 0) {
    v.velX = v.velX > 0 ? v.velX - 0.2 : v.velX + 0.2;
    if (v.velX >= -0.2 && v.velX <= 0.2)
      v.velX = 0;
  }
  if (Game::plr.isJumping() && v.velY > 0 && v.velY < 10) {
    v.velY = 10;
  }
  if (Game::plr.isJumping()) {
    v.velY += 1;
  }
  if (v.velY > 20) {
    v.velY = 20;
  }
  int deltaY = v.velY;
  int deltaX = v.velX * Game::plr.getSpeed();
  for (auto tile : tiles) {
    SDL_Rect pHor = {.x = plrPos.x + deltaX,
                     .y = plrPos.y,
                     .w = Game::plr.getSize(),
                     .h = Game::plr.getSize()};
    SDL_Rect pVert = {.x = plrPos.x,
                      .y = plrPos.y + deltaY,
                      .w = Game::plr.getSize(),
                      .h = Game::plr.getSize()};
    SDL_Rect t = tile.getDest();
    if (SDL_HasIntersection(&pHor, &t) == SDL_TRUE) {
      if (v.velX < 1) {
        plrPos.x = t.x + t.w;
      } else if (v.velX > 0) {
        plrPos.x = t.x - Game::plr.getSize();
      }
      if (Game::plr.isJumping()) {
        v.velX = 0;
        v.velY = 10;
      }
      deltaX = 0;
    }
    if (SDL_HasIntersection(&pVert, &t) == SDL_TRUE) {
      if (v.velY < 0) {
        plrPos.y = t.y + t.h;
        v.velX = 0;
        v.velY = 10;
      } else {
        plrPos.y = t.y - Game::plr.getSize();
        v.velX = 0;
        v.velY = 10;
        Game::plr.setIsJumping(false);
      }
      deltaY = 0;
    }
  }
  Game::plr.setVelocity(v.velX, v.velY);
  Game::plr.move(plrPos.x + deltaX, int(plrPos.y + deltaY));
}

void Game::endGame() {
  Game::window->cleanUp();
  SDL_Quit();
}
