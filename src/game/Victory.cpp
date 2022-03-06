#include "Victory.hpp"

void Victory::initialize(SDL_Renderer* renderer) {
  Logger::okay("Initializing victory screen!");

  this->renderer = renderer;

  loadAssets();
}

void Victory::loadAssets() {
	Logger::okay("Loading the victory screen!");

	SDL_Surface* asset = SDL_LoadBMP("../assets/victory.bmp");
	texture = SDL_CreateTextureFromSurface(this->renderer, asset);
}

void Victory::draw() {
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