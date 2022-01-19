#include "headers/GameOver.h"

void GameOver::initialize(SDL_Renderer* renderer) {
  Logger::okay("Initializing menu!");

  this->renderer = renderer;

  loadAssets();
}

void GameOver::loadAssets() {
	Logger::okay("Loading the menu & selector!");

	SDL_Surface* assetBg = SDL_LoadBMP("src/assets/game_over.bmp");
	texture = SDL_CreateTextureFromSurface(this->renderer, assetBg);
}

void GameOver::draw() {
	SDL_SetRenderDrawColor(
		this->renderer,
		255,
		255,
		255,
		0
	);

	SDL_RenderClear(this->renderer);

	SDL_RenderCopy(
		this->renderer,
		texture,
		NULL,
		&render
	);
}