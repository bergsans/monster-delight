#include "../include/Window.h"
#include "../include/Entity.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Window::Window() : window(NULL), renderer(NULL) {
  window = SDL_CreateWindow(
      "...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720,
      SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_MAXIMIZED);
  //      SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
  //                       1280, 720, SDL_WINDOW_SHOWN);

  if (window == NULL) {
    std::cerr << SDL_GetError() << std::endl;
  }
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture *Window::initTexture(const char *p_filePath) {
  SDL_Texture *texture;
  texture = IMG_LoadTexture(renderer, p_filePath);
  if (texture == NULL) {
    std::cerr << SDL_GetError() << std::endl;
  }
  return texture;
}

void Window::cleanUp() { SDL_DestroyWindow(window); }

void Window::clear() { SDL_RenderClear(renderer); }

void Window::render(SDL_Rect dst, SDL_Rect src, SDL_Texture *texture) {
  if (texture == NULL) {
    std::cerr << "No image found.";
    exit(1);
  }
  SDL_RenderCopy(renderer, texture, &src, &dst);
}

void Window::display() { SDL_RenderPresent(renderer); }
