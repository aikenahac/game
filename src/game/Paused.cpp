#include "Paused.hpp"

void Paused::initialize(SDL_Renderer* renderer) {
  Logger::okay("Initializing paused screen!");

  this->renderer = renderer;

  loadAssets();
}

void Paused::loadAssets() {
	Logger::okay("Loading the paused screen!");

	SDL_Surface* asset = SDL_LoadBMP("../assets/paused.bmp");
	texture = SDL_CreateTextureFromSurface(this->renderer, asset);
}

void Paused::draw() {
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