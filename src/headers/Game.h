#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#include "Ally.h"
#include "Config.h"
#include "Enemy.h"
#include "HealthBar.h"
#include "Logger.h"
#include "Map.h"
#include "Player.h"
#include "Menu.h"
#include "GameOver.h"
#include "Animal.h"

class Game {
  private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    bool isRunning;

    Player player;
    Map map;

    Menu menu;
    GameOver goScreen;

    std::vector<Ally> allies;
    std::vector<Enemy> enemies;
    std::vector<Animal> animals;

    HealthBar healthBar;

    bool playing = false;
    bool justDied = false;
    int level = 0;

    bool keys[322] = {false};

    void handleKeyboard();
    void gameOverScreen();
    void gameScreen();

    void setScreen(int);

    void select();

    void clean();

    void gameOver();

  public:
    Game();
    void run();
    
};