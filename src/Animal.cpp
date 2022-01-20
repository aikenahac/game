#include "headers/Animal.h"

Animal::Animal() {
  int minX = 100;
  int maxX = WIDTH + 1;

  int minY = 100;
  int maxY = HEIGHT + 1;

  int x = (rand() % (maxX - minX) + minX) - 100;
  int y = (rand() % (maxY - minY) + minY) - 100;

  this->render = {
    x,
    y,
    SPRITE_SIZE * 2,
    SPRITE_SIZE * 2
  };
}

void Animal::initialize(SDL_Renderer* renderer) {
  Logger::okay("Initializing an ally!");

	this->renderer = renderer;
	
	loadAsset();
}

void Animal::loadAsset() {
  SDL_Surface* animal;

  char temp[40];

  strcpy(temp, "src/assets/animals/");
  strcat(temp, paths[rand()%3]);

  animal = SDL_LoadBMP(temp);
  
  texture = SDL_CreateTextureFromSurface(renderer, animal);
}

void Animal::draw() {
  SDL_RenderCopy(
    renderer,
    texture,
    NULL,
    &render
  );
}