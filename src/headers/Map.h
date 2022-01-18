#pragma once

#include <SDL2/SDL.h>

#include "Player.h"
#include "Config.h"
#include "Logger.h"

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