#include "headers/Ally.h"

Ally::Ally() {
  int minX = 100;
  int maxX = WIDTH + 1;

  int minY = 100;
  int maxY = HEIGHT + 1;

  int x = rand() % (maxX - minX) + minX;
  int y = rand() % (maxY - minY) + minY;

  this->render = {
    x,
    y,
    SPRITE_SIZE,
    SPRITE_SIZE
  };
}

void Ally::initialize(SDL_Renderer* renderer) {
  Logger::okay("Initializing an ally!");

	this->renderer = renderer;
	
	loadSprite();
}

void Ally::loadSprite() {
  Logger::okay("Loading ally textures!");

  SDL_Surface* ally;

  char temp[40];

  for (int i = 0; i < 10; i++) {
    strcpy(temp, "src/assets/allies/");
    strcat(temp, paths[i]);
    
    ally = SDL_LoadBMP(temp);
  
    assets[i] = SDL_CreateTextureFromSurface(renderer, ally);
  }
}