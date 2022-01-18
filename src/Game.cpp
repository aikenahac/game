#include "headers/Game.h"
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
			SDL_WINDOW_SHOWN
		);

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

	player.initialize(renderer);
	map.initialize(renderer);


  while(isRunning) {
    while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				isRunning = false;
			}
			else if (event.key.keysym.sym == SDLK_LSHIFT && event.key.keysym.sym == SDLK_RSHIFT) continue;
			else if(event.type == SDL_KEYDOWN) keys[event.key.keysym.sym] = true;
			else if(event.type == SDL_KEYUP) keys[event.key.keysym.sym] = false;
		}

		handleKeyboard();

		map.draw();
		player.draw();

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::handleKeyboard() {
	if(keys[SDLK_w]) player.moveUp();
	if(keys[SDLK_s]) player.moveDown();
	if(keys[SDLK_a]) player.moveLeft();
	if(keys[SDLK_d]) player.moveRight();

	if (keys[SDLK_LESS]) player.setSpeed(SPRINT_SPEED);
	if (!keys[SDLK_LESS]) player.setSpeed(WALK_SPEED);

	if(!keys[SDLK_w] && !keys[SDLK_s] && !keys[SDLK_a] && !keys[SDLK_d]) {
		player.walking(false);
	}
}