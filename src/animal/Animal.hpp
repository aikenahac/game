#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#include "../logger/Logger.hpp"
#include "../Config.hpp"

class Animal {
  private:
    char paths[3][11] = {
      "bunny.bmp",
      "dog.bmp",
      "cat.bmp",
    };

    SDL_Rect render = {
      100,
      100,
      SPRITE_SIZE * 2,
      SPRITE_SIZE * 2
    };

    SDL_Renderer* renderer;
    SDL_Texture* texture;

    void detectBorderCollision();

    void loadAsset();

  public:
    Animal();

    void initialize(SDL_Renderer*);
    void draw();

    SDL_Rect getRect();

    Animal getSelf();
};  