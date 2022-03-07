#include "Enemy.hpp"

Enemy::Enemy() {
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

void Enemy::initialize(SDL_Renderer* renderer) {
  Logger::okay("Initializing an enemy!");

	this->renderer = renderer;
	
	loadSprite();
}

void Enemy::loadSprite() {

  SDL_Surface* ally;

  for (int i = 0; i < 10; i++) {
    std::string temp = "../assets/enemies/" + paths[i];
    
    ally = SDL_LoadBMP(temp.c_str());
  
    assets[i] = SDL_CreateTextureFromSurface(renderer, ally);
  }
}