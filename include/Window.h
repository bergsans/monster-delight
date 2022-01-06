#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.h"

class Window {
public:
  Window();
  SDL_Texture *initTexture(const char *p_filePath);
  void cleanUp();
  void clear();
  void render(SDL_Rect dst, SDL_Rect src, SDL_Texture *texture);
  void display();

private:
  SDL_Window *window;
  SDL_Texture *texture;
  SDL_Renderer *renderer;
};
