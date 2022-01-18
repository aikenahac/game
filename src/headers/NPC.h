#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <chrono>
#include <cstring>

#include "Logger.h"
#include "Config.h"

class NPC {
  protected:
    char paths[10][11] = {
      "down1.bmp",
      "down2.bmp",
      "down3.bmp",
      "up1.bmp",
      "up2.bmp",
      "up3.bmp",
      "left1.bmp",
      "left2.bmp",
      "right1.bmp",
      "right2.bmp"
    };

    SDL_Rect render = {
      100,
      100,
      SPRITE_SIZE,
      SPRITE_SIZE
    };

    SDL_Renderer* renderer;
    SDL_Texture* assets[10];

    bool isWalking = false;
    bool dead = false;

    uint8_t direction = 0;
    uint8_t frame = 0;

    int speed = WALK_SPEED;

    std::chrono::system_clock::time_point lastFrame = std::chrono::system_clock::now();
	  std::chrono::system_clock::time_point timeNow;

    void detectBorderCollision();

  public:
    void setDirection(uint8_t);
    void walking(bool);
    void draw();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void movement();

    SDL_Rect getRect();

    void detectCollision(SDL_Rect);
};  