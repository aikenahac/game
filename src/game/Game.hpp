#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdio>

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
#include "../game/Paused.hpp"
#include "../animal/Animal.hpp"
#include "../leaderboard/Leaderboard.hpp"
#include "../replay/Replay.hpp"
#include "../utils/Utils.hpp"

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
    Leaderboard leaderboard;
    Replay replay;
    Paused paused;

    std::vector<Ally*> allies;
    std::vector<Enemy*> enemies;
    std::vector<Animal*> animals;

    HealthBar healthBar;

    bool playing = false;
    bool justDied = false;
    bool justWon = false;
    bool showLeaderboard = false;
    bool runningReplay = false;

    bool isPaused = false;

    int level = 0;

    int score = 0;

    int level1Allies = 1;
    int level1Enemies = 2;
    int level1Animals = 3;

    int level2Allies = 2;
    int level2Enemies = 3;
    int level2Animals = 4;

    int level3Allies = 1;
    int level3Enemies = 4;
    int level3Animals = 8;

    bool keys[322] = {false};

    std::string playerName;

    void handleKeyboard();
    void gameOverScreen();
    void gameScreen();

    void setScreen(int);

    void select();

    void clean();

    void gameOver();

    void victory();

    void runReplay();

    void cleanEntities();

    void updateScore(int score);
    void saveScore();
    void loadScores();

  public:
    Game(bool fullscreen);
    void run();
};