#include "../include/Entity.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Entity::Entity(float _x, float _y, float _srcX, float _srcY, float _size)
    : x(_x), y(_y), srcX(_srcX), srcY(_srcY), size(_size) {}

SDL_Rect Entity::getDest() {
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  dest.w = size;
  dest.h = size;
  return dest;
}

SDL_Rect Entity::getSrc() {
  SDL_Rect src;
  src.x = srcX;
  src.y = srcY;
  src.w = size;
  src.h = size;
  return src;
}

void Entity::move(float dx, float dy) {
  x += dx;
  y += dy;
}
