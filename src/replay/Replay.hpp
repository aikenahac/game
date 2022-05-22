#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

#include "../logger/Logger.hpp"
#include "../Config.hpp"
#include "../map/Map.hpp"
#include "../player/Player.hpp"
#include "../utils/Utils.hpp"

class Replay {
  private:
    Map map;
    Player player;

    SDL_Renderer* renderer;

  public:
    void initialize(SDL_Renderer*);
    void start();
    void clear();
};