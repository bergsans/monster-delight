#pragma once
#include "Entity.h"
#include <map>

struct Pos {
  int x;
  int y;
};

struct Velocity {
  float velX;
  float velY;
};

struct PlrData {
  Pos pos = {.x = 450, .y = 100};
  Velocity vel = {.velX = 0, .velY = 0};
  bool idle = false;
  bool direction = false;
  bool isJumping = true;
  int speed = 5;
};

class Player {
public:
  Player();
  SDL_Rect getSrc();
  SDL_Rect getDest();
  Pos getSpritePos(int si);
  void move(int x, int y);
  Pos getPlrPos();
  Velocity getVelocity();
  void setVelocity(float velX, float velY);
  int getSpeed();
  bool getIdle();
  void setIdle(bool value);
  bool getDirection();
  void setDirection(bool value);
  bool isJumping();
  void setIsJumping(bool value);
  void incSpriteIndex();
  int getSize();

private:
  PlrData state;
  int size = 50;
  int spriteIndex = 0;
};
