#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity {
public:
  Entity(float _x, float _y, float _srcX, float _srcY, float _size);
  SDL_Rect getSrc();
  SDL_Rect getDest();
  void move(float dx, float dy);

private:
  float x, y, srcX, srcY, size;
};
