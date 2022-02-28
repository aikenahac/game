#pragma once

#include <SDL2/SDL.h>

#include "../player/Player.hpp"
#include "../Config.hpp"
#include "../logger/Logger.hpp"

class Map {
  private:
    SDL_Texture* map;
    
    SDL_Rect render = {
      0,
      0,
      WIDTH,
      HEIGHT
    };

    SDL_Renderer* renderer;
    
    void loadMap();

  public:
    void initialize(SDL_Renderer*);

    void draw();
};