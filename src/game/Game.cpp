#include "Game.hpp"
#include <SDL2/SDL.h>

Game::Game() {
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
        SDL_WINDOW_SHOWN);

    if (window == NULL) {
      Logger::error("SDL window error!");
      std::cout << SDL_GetError() << '\n';
      Logger::error("Window error");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    isRunning = true;
  }
}

void Game::run() {
  srand(time(NULL));

	healthBar.initialize(renderer, player);

  allies.clear();
  enemies.clear();
  animals.clear();

	menu.initialize(renderer);
	goScreen.initialize(renderer);

  player.initialize(renderer);
  map.initialize(renderer);

  for (int i = 0; i < 3; i++) {
    Ally ally = Ally();

    ally.initialize(renderer);

    allies.push_back(ally);
  }

  for (int i = 0; i < 4; i++) {
    Enemy enemy = Enemy();

    enemy.initialize(renderer);

    enemies.push_back(enemy);
  }

  for (int i = 0; i < 3; i++) {
    Animal animal = Animal();

    animal.initialize(renderer);

    animals.push_back(animal);
  }

  while (isRunning) {

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        isRunning = false;
      } else if (event.key.keysym.sym == SDLK_LSHIFT && event.key.keysym.sym == SDLK_RSHIFT)
        continue;

			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_e) menu.moveDown();
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q) menu.moveUp();
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) select();

      else if (event.type == SDL_KEYDOWN)
        keys[event.key.keysym.sym] = true;
      else if (event.type == SDL_KEYUP)
        keys[event.key.keysym.sym] = false;
    }

    handleKeyboard();

    if (playing) setScreen(GAME_SCREEN);
		else if (justDied) setScreen(GAME_OVER_SCREEN);
		else setScreen(HOME_SCREEN);

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

	if (keys[SDLK_c]) {
		player.resetLives();
		justDied = false;
	}

  if (!keys[SDLK_w] && !keys[SDLK_s] && !keys[SDLK_a] && !keys[SDLK_d]) {
    player.walking(false);
  }
}

void Game::gameScreen() {
  map.draw();

  healthBar.draw();

  for (auto ally = allies.begin(); ally != allies.end(); ally++) {
    ally->draw();
    std::string type = "ally";
    player.detectCollision(ally->getRect(), type);
  }

  for (auto ally = allies.begin(); ally != allies.end(); ally++) {
    ally->movement();
    for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++) {
      SDL_Rect enemyRect = enemy->getRect();
      ally->detectCollision(enemyRect);
    }
  }

  for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++) {
    enemy->draw();
  }

  for (auto animal = animals.begin(); animal != animals.end(); animal++) {
    animal->draw();

    player.detectCollection(animal->getRect(), animal->getSelf(), animals);
  }

  for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++) {
    enemy->movement();

    std::string type = "enemy";
    player.detectCollision(enemy->getRect(), type);

		healthBar.setLives(player.getLives());

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
    case GAME_SCREEN:
			SDL_RenderClear(renderer);
      gameScreen();
      break;
  }
}

void Game::select() {
	switch (menu.getSelection()) {
		case START:
			playing = true;
			break;
		case LOAD_REPLAY:
			isRunning = false;
			break;
		case QUIT:
			isRunning = false;
			break;
	}
}

void Game::gameOver() {
  SDL_RenderClear(renderer);
	playing = false;
	justDied = true;
}

void Game::clean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}