#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#include "../Config.hpp"
#include "../logger/Logger.hpp"
#include "../player/Player.hpp"

class Heart {
  private:
    SDL_Rect render = {
      100,
      100,
      HEART_SIZE,
      HEART_SIZE
    };

    SDL_Renderer* renderer;
	  SDL_Texture* texture;

    void loadAsset();

  public:
    void initialize(SDL_Renderer*, int, int);

    void draw();
};

class HealthBar {
  private:
    int lives;

    Heart hearts[3];

  public:
    void initialize(SDL_Renderer*, Player);
    void draw();

    void setLives(int);
};