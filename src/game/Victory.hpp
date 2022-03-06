#pragma once

#include <SDL2/SDL.h>

#include "../player/Player.hpp"
#include "../Config.hpp"
#include "../logger/Logger.hpp"

class Victory {
  private:
    SDL_Texture* texture;
    
    SDL_Rect render = {
      0,
      0,
      WIDTH,
      HEIGHT
    };

    SDL_Renderer* renderer;
    
    void loadAssets();

  public:
    void initialize(SDL_Renderer*);

    void draw();
};