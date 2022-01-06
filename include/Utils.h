#pragma once
#include "../include/Entity.h"
#include "../include/Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace util {
std::map<int, Pos> getTilePositions() {
  Pos temp;
  std::map<int, Pos> tilePos;
  temp.x = 0;
  temp.y = 1100;
  tilePos.insert(std::make_pair(1, temp));
  return tilePos;
}

std::vector<Entity> getLevel(std::string fileName) {
  std::ifstream f(fileName);
  std::vector<Entity> level;
  std::string line;
  std::map<int, Pos> tilePos = getTilePositions();
  int y = 0;
  if (f.is_open()) {
    while (getline(f, line)) {
      for (int i = 0; i < 40; i++) {
        char c = line[i];
        int x = (int)c - 48;
        if (x != 0) {
          Pos p = tilePos[x];
          Entity t(i * 32, y * 32, p.x, p.y, 32);
          level.push_back(t);
        }
      }
      y++;
    }
    f.close();
  }
  return level;
}
} // namespace util
