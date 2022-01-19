#pragma once

#include <SDL2/SDL.h>

#include "Player.h"
#include "Config.h"
#include "Logger.h"

class Menu {
  private:
    SDL_Texture* texture;
    SDL_Texture* selectorTexture;
    
    SDL_Rect render = {
      0,
      0,
      WIDTH,
      HEIGHT
    };

    SDL_Rect selector = {
      800,
      80,
      271,
      180
    };

    SDL_Renderer* renderer;

    int selection = 0;
    
    void loadAssets();

  public:
    void initialize(SDL_Renderer*);

    void draw();
    void setSelection();
    int getSelection();

    void moveDown();
    void moveUp();
};