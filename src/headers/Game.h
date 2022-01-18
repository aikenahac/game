#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include "Logger.h"
#include "Config.h"
#include "Player.h"
#include "Map.h"

class Game {
  private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    bool isRunning;

    Player player;
    Map map;

    bool keys[322] = { false };

    void handleKeyboard();

  public:
    Game();
    void run();
};