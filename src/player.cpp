#include "../include/Player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Player::Player() {}

void Player::incSpriteIndex() {
  if (state.isJumping) {
    spriteIndex = spriteIndex + 1 < 5 ? spriteIndex + 1 : 0;
  } else {
    spriteIndex = spriteIndex + 1 < 6 ? spriteIndex + 1 : 0;
  }
}

SDL_Rect Player::getDest() {
  SDL_Rect dest = {.x = state.pos.x, .y = state.pos.y, .w = size, .h = size};
  return dest;
}

Pos Player::getSpritePos(int si) {
  Pos temp;
  if (state.isJumping) {
    temp.x = 0;
    temp.y = 600;
    int mod = si * 50;
    temp.y += mod;
    if (state.direction) {
      temp.y += 250;
    }
    return temp;
  }
  if (!state.idle) {
    temp.x = 0;
    temp.y = 1132;
    int mod = si * 50;
    temp.y += mod;
    if (state.direction) {
      temp.y += 300;
    }
    return temp;
  }
  temp.x = 0;
  temp.y = 0;
  int mod = si * 50;
  temp.y += mod;
  if (state.direction) {
    temp.y += 300;
  }
  return temp;
}

Velocity Player::getVelocity() { return state.vel; }
void Player::setVelocity(float velX, float velY) {
  state.vel = {.velX = velX, .velY = velY};
}

bool Player::getIdle() { return state.idle; }
void Player::setIdle(bool value) { state.idle = value; }

bool Player::getDirection() { return state.direction; }
void Player::setDirection(bool value) { state.direction = value; }

bool Player::isJumping() { return state.isJumping; }
void Player::setIsJumping(bool value) { state.isJumping = value; }

SDL_Rect Player::getSrc() {
  Pos temp_pos = this->getSpritePos(spriteIndex);
  SDL_Rect dest;
  dest.x = temp_pos.x;
  dest.y = temp_pos.y;
  dest.w = size;
  dest.h = size;
  return dest;
}

Pos Player::getPlrPos() { return state.pos; }
int Player::getSize() { return size; }
int Player::getSpeed() { return state.speed; }

void Player::move(int dx, int dy) { state.pos = {.x = dx, .y = dy}; }
