#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#include "../ally/Ally.hpp"
#include "../Config.hpp"
#include "../enemy/Enemy.hpp"
#include "../health_bar/HealthBar.hpp"
#include "../logger/Logger.hpp"
#include "../map/Map.hpp"
#include "../player/Player.hpp"
#include "../menu/Menu.hpp"
#include "../game/GameOver.hpp"
#include "../game/Victory.hpp"
#include "../animal/Animal.hpp"

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
    Victory victoryScreen;

    std::vector<Ally*> allies;
    std::vector<Enemy*> enemies;
    std::vector<Animal*> animals;

    HealthBar healthBar;

    bool playing = false;
    bool justDied = false;
    bool justWon = false;
    
    int level = 0;

    int level1Animals = 3;
    int level1Enemies = 2;
    int level1Allies = 1;

    int level2Animals = 6;
    int level2Enemies = 3;
    int level2Allies = 2;

    int level3Animals = 8;
    int level3Enemies = 4;
    int level3Allies = 0;

    bool keys[322] = {false};

    void handleKeyboard();
    void gameOverScreen();
    void gameScreen();

    void setScreen(int);

    void select();

    void clean();

    void gameOver();

    void victory();

  public:
    Game();
    void run();
    
};