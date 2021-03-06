#include "Game.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

Game::Game(bool fullscreen) {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    Logger::error("SDL crashed and burned!");
    Logger::error("SDL ERROR: ");
    std::cout << SDL_GetError() << '\n';
    throw "SDL INIT ERROR";
  } else {
    window = SDL_CreateWindow(
        "Ne Testiranju na Živalih - Aiken Tine Ahac",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        fullscreen ? SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN : SDL_WINDOW_SHOWN
        );

    if (window == NULL) {
      Logger::error("SDL window error!");
      std::cout << SDL_GetError() << '\n';
      Logger::error("Window error");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    TTF_Init();

    isRunning = true;
  }
}

void Game::run() {
  srand(time(NULL));

  std::cout << "What is your name? ";
  std::cin >> this->playerName;

  Logger::info("Player: " + playerName);

	healthBar.initialize(renderer, player);

	menu.initialize(renderer);
	goScreen.initialize(renderer);
	victoryScreen.initialize(renderer);
  paused.initialize(renderer);
  leaderboard.initialize(renderer);

  replay.initialize(renderer);

  player.initialize(renderer);
  map.initialize(renderer);

  for (int i = 0; i < 1; i++) {
    Ally *ally = new Ally();

    ally->initialize(renderer);

    allies.push_back(ally);
  }

  for (int i = 0; i < 2; i++) {
    Enemy *enemy = new Enemy();

    enemy->initialize(renderer);

    enemies.push_back(enemy);
  }

  for (int i = 0; i < level1Animals; i++) {
    Animal *animal = new Animal();

    animal->initialize(renderer);

    animals.push_back(animal);
  }

  while (isRunning) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        isRunning = false;
      } else if (event.key.keysym.sym == SDLK_LSHIFT && event.key.keysym.sym == SDLK_RSHIFT) {
        continue;
      }

			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_e) menu.moveDown();
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q) menu.moveUp();
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) select();

      else if (event.type == SDL_KEYDOWN)
        keys[event.key.keysym.sym] = true;
      else if (event.type == SDL_KEYUP)
        keys[event.key.keysym.sym] = false;
    }

    handleKeyboard();

    if (isPaused) this->setScreen(PAUSED_SCREEN);
    else if (playing) this->setScreen(GAME_SCREEN);
		else if (justDied) this->setScreen(GAME_OVER_SCREEN);
    else if (justWon) this->setScreen(VICTORY_SCREEN);
    else if (showLeaderboard) this->setScreen(LEADERBOARD_SCREEN);
    else if (runningReplay) this->setScreen(REPLAY_SCREEN);
		else this->setScreen(HOME_SCREEN);

    SDL_RenderPresent(renderer);
  }

  this->clean();
}

void Game::handleKeyboard() {
  if (keys[SDLK_w]) player.moveUp();
  if (keys[SDLK_s]) player.moveDown();
  if (keys[SDLK_a]) player.moveLeft();
  if (keys[SDLK_d]) player.moveRight();

  if (keys[SDLK_LESS]) player.setSpeed(SPRINT_SPEED);
  if (!keys[SDLK_LESS]) player.setSpeed(WALK_SPEED);

	if (keys[SDLK_c] && (justWon == true || justDied == true || showLeaderboard == true || runningReplay == true)) {
		player.resetLives();
		justDied = false;
    justWon = false;
    showLeaderboard = false;
    runningReplay = false;
    score = 0;
	}

  if (keys[SDLK_p] && isPaused == false) {
    isPaused = true;
  } 
  
  if (keys[SDLK_r] && isPaused == true) {
    isPaused = false;
  }

  if (!keys[SDLK_w] && !keys[SDLK_s] && !keys[SDLK_a] && !keys[SDLK_d]) {
    player.walking(false);
  }
}

void Game::gameScreen() {
  map.draw();

  healthBar.draw();

  if (animals.empty() || enemies.empty() || allies.empty()) {
    std::cout << "Vectors are empty.\n\n";
    int animalCount, allyCount, enemyCount;

    switch (level) {
      case 1:
        animalCount = level2Animals;
        allyCount = level2Allies;
        enemyCount = level2Enemies;
        break;
      case 2:
        animalCount = level3Animals;
        allyCount = level3Allies;
        enemyCount = level3Enemies;
        break;
      default:
        animalCount = level1Animals;
        allyCount = level1Allies;
        enemyCount = level1Enemies;
    }
    
    for (int i = 0; i < allyCount; i++) {
      Ally *ally = new Ally();

      ally->initialize(renderer);

      allies.push_back(ally);
    }

    for (int i = 0; i < enemyCount; i++) {
      Enemy *enemy = new Enemy();

      enemy->initialize(renderer);

      enemies.push_back(enemy);
    }

    for (int i = 0; i < animalCount; i++) {
      Animal *animal = new Animal();

      animal->initialize(renderer);

      animals.push_back(animal);
    }
  }

  for (std::vector<Ally*>::iterator ally = allies.begin(); ally != allies.end(); ally++) {
    (*ally)->draw();
    std::string type = "ally";
    player.detectCollision((*ally)->getRect(), type);
  }

  for (std::vector<Ally*>::iterator ally = allies.begin(); ally != allies.end(); ally++) {
    for (std::vector<Enemy*>::iterator enemy = enemies.begin(); enemy != enemies.end(); enemy++) {
      (*enemy)->draw();
      (*ally)->movement((*enemy)->getRect());
    }
  }

  for (std::vector<Animal*>::iterator animal = animals.begin(); animal != animals.end(); animal++) {
    (*animal)->draw();

    bool collection = player.detectCollection((*animal)->getRect(), *animal, animals);

    if (collection) {
      this->updateScore(100);
      if (level == 0) {
        level1Animals--;
        if (level1Animals == 0) {
          allies.clear();
          enemies.clear();
          level++;
          Logger::info("Moving to level: " + std::to_string(level));
        };
      } else if (level == 1) {
          level2Animals--;
          if (level2Animals == 0) {
            allies.clear();
            enemies.clear();
            level++;
            Logger::info("Moving to level: " + std::to_string(level));
          }
      } else if (level == 2) {
          level3Animals--;
          if (level3Animals == 0) {
            allies.clear();
            enemies.clear();
            victory();
          }
      }
    }
  }

  for (std::vector<Enemy*>::iterator enemy = enemies.begin(); enemy != enemies.end(); enemy++) {
    (*enemy)->movement(player.getRect());

    std::string type = "enemy";
    bool collision = player.detectCollision((*enemy)->getRect(), type);

		if (collision) {
      healthBar.setLives(player.getLives());

      this->updateScore(-20);
    }

		if (player.getLives() == 0) gameOver();
  }

  player.draw();
}

void Game::setScreen(int screen) {
  switch (screen) {
    case HOME_SCREEN:
			SDL_RenderClear(renderer);
			menu.draw();
      break;
    case GAME_OVER_SCREEN:
			SDL_RenderClear(renderer);
      goScreen.draw();
      break;
    case VICTORY_SCREEN:
      SDL_RenderClear(renderer);
      victoryScreen.draw();
      break;
    case GAME_SCREEN:
			SDL_RenderClear(renderer);
      gameScreen();
      break;
    case LEADERBOARD_SCREEN:
      SDL_RenderClear(renderer);
      leaderboard.draw();
      break;
    case REPLAY_SCREEN:
      SDL_RenderClear(renderer);
      replay.start();
      break;
    case PAUSED_SCREEN:
      SDL_RenderClear(renderer);
      paused.draw();
      break;
  }
}

void Game::select() {
	switch (menu.getSelection()) {
		case START:
      replay.clear();
			playing = true;
			break;
    case LEADERBOARD:
      showLeaderboard = true;
      break;
		case LOAD_REPLAY:
			runningReplay = true;
			break;
		case QUIT:
			isRunning = false;
			break;
	}
}

void Game::victory() {
  SDL_RenderClear(renderer);
  saveScore();
	playing = false;
  justWon = true;
}

void Game::gameOver() {
  SDL_RenderClear(renderer);
  saveScore();
	playing = false;
	justDied = true;
}

void Game::clean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
  TTF_Quit();
}

void Game::cleanEntities() {
  for (std::vector<Enemy*>::iterator enemy = enemies.begin(); enemy != enemies.end(); enemy++) {
    enemies.erase(std::remove(enemies.begin(), enemies.end(), *enemy), enemies.end());
    delete (*enemy);
  }

  for (std::vector<Ally*>::iterator ally = allies.begin(); ally != allies.end(); ally++) {
    allies.erase(std::remove(allies.begin(), allies.end(), *ally), allies.end());
    delete (*ally);
  }

  for (std::vector<Animal*>::iterator animal = animals.begin(); animal != animals.end(); animal++) {
    animals.erase(std::remove(animals.begin(), animals.end(), *animal), animals.end());
    delete (*animal);
  }
}

void Game::saveScore() {
  std::string msg = "Saving " + this->playerName + "'s score of ";

  msg += std::to_string(this->score);

  std::ifstream dataRead("../Leaderboard.bin", std::ios::binary);
  std::ofstream dataWrite("../tmp.bin", std::ios::binary);

  Save temp;
  Save newSave;

  if (dataWrite.is_open() && dataRead.is_open()) {
    strcpy(newSave.player, playerName.c_str());
    newSave.score = score;

    bool written = false;

    while(dataRead.read((char *) &temp, sizeof(Save))) {
      if (newSave.score > temp.score && !written) {
        dataWrite.write((char*)&newSave, sizeof(Save));
        written = true;
      }
      dataWrite.write((char*)&temp, sizeof(Save));
    }

    if (!written) {
      dataWrite.write((char*)&newSave, sizeof(Save));
      written = true;
    }
  }

  dataWrite.close();
  dataRead.close();

  remove("../Leaderboard.bin");
  rename("../tmp.bin", "../Leaderboard.bin");
}

void Game::updateScore(int score) {
  this->score = this->score + score;

  std::string msg = "Score is now: ";

  msg += std::to_string(this->score);

  Logger::info(msg);
}

void Game::loadScores() {
  std::ifstream data("../Leaderboard.bin", std::ios::binary);

  Logger::info("Loading scores");
  
  Save curr;

  if (data.is_open()) {
    while (data.read((char *) &curr, sizeof(Save))) {
      std::cout << curr.player << " " << curr.score << "\n";
    }
  }

  data.close();
}