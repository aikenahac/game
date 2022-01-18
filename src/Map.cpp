#include "headers/Map.h"

void Map::initialize(SDL_Renderer* renderer) {
  Logger::okay("Initializing map!");

  this->renderer = renderer;

  loadMap();
}

void Map::loadMap() {
	Logger::okay("Loading the map!");

	SDL_Surface* assetMap = SDL_LoadBMP("src/assets/map.bmp");
	map = SDL_CreateTextureFromSurface(this->renderer, assetMap);
}

void Map::draw() {
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
		map,
		NULL,
		&render
	);
}