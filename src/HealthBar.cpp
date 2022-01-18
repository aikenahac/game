#include "headers/HealthBar.h"

void Heart::initialize(SDL_Renderer* renderer, int x, int y) {
  this->render = {
    x,
    y,
    HEART_SIZE,
    HEART_SIZE
  };

  this->renderer = renderer;

  loadAsset();
}

void Heart::loadAsset() {

  SDL_Surface* heart;

  heart = SDL_LoadBMP("src/assets/gui/heart.bmp");

  texture = SDL_CreateTextureFromSurface(this->renderer, heart);
}

void Heart::draw() {
  SDL_RenderCopy(
    renderer,
    texture,
    NULL,
    &render
  );
}

void HealthBar::initialize(SDL_Renderer* renderer, Player player) {
  lives = player.getLives();

  for (int i = 0; i < lives; i++) {
    hearts[i].initialize(renderer, WIDTH - 60 - i*40, 10);
    // hearts[i].initialize(renderer, 600, 600 - i*50);
  }
}

void HealthBar::draw() {
  for (int i = 0; i < lives; i++) {
    hearts[i].draw();
  }
}