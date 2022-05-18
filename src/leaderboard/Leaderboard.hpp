#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#include "../utils/Utils.hpp"
#include "../Config.hpp"
#include "../logger/Logger.hpp"
#include "../utils/Utils.hpp"

class Leaderboard {
  private:
    SDL_Texture* texture;

    std::vector<std::string> spots; 

    SDL_Rect render = {
      0,
      0,
      WIDTH,
      HEIGHT,
    };

    SDL_Renderer *renderer;

    void loadAssets();

    void loadScores();

  public:
    void initialize(SDL_Renderer*);

    void draw();
};