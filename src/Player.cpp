#include "headers/Player.h"

Player::Player() {
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

void Player::initialize(SDL_Renderer* renderer) {
	Logger::okay("Initializing player!");

	this->renderer = renderer;
	
	loadPlayerSprite();
}

void Player::loadPlayerSprite() {
  Logger::okay("Loading player textures!");

  SDL_Surface* player;

  char temp[40];

  for (int i = 0; i < 10; i++) {
    strcpy(temp, "src/assets/character/");
    strcat(temp, paths[i]);

    player = SDL_LoadBMP(temp);
  
    assets[i] = SDL_CreateTextureFromSurface(renderer, player);
  }
}

void Player::draw() {
  if (isWalking) {
    timeNow = std::chrono::system_clock::now();
		
		if((timeNow - lastFrame).count() > 100000000){
			switch (direction) {
			case 0:
			case 3:
				frame++;
				if(frame > 2) frame = 1;
				break;
			case 6:
			case 8:
				frame++;
				if(frame > 1) frame = 0;
				break;
			}
			lastFrame = timeNow;
		}
  } else frame = 0;

  switch (direction) {
		case 6:
		case 8:
			if(frame > 1) frame = 0;
			break;
	}

  SDL_RenderCopy(
    renderer,
    assets[direction + frame],
    NULL,
    &render
  );
}

void Player::setDirection(uint8_t direction) {
  this->direction = direction;
}

void Player::walking(bool isWalking) {
  this->isWalking = isWalking;
}

void Player::detectBorderCollision() {
  if (render.x < 0) {
    render.x = 0;
  }
  if (render.x > WIDTH - SPRITE_SIZE) {
    render.x = WIDTH - SPRITE_SIZE;
  }
  if (render.y < 0) {
    render.y = 0;
  }
  if (render.y > HEIGHT - SPRITE_SIZE) {
    render.y = HEIGHT - SPRITE_SIZE;
  }
}

void Player::setSpeed(int speed) {
  this->speed = speed;
}

void Player::moveUp() {
  this->setDirection(3);
  this->walking(true);

  this->render.y -= speed;
  detectBorderCollision();
}

void Player::moveDown() {
  this->setDirection(0);
  this->walking(true);

  this->render.y += speed;
  detectBorderCollision();
}

void Player::moveLeft() {
  this->setDirection(6);
  this->walking(true);

  this->render.x -= speed;
  detectBorderCollision();
}

void Player::moveRight() {
  this->setDirection(8);
  this->walking(true);

  this->render.x += speed;
  detectBorderCollision();
}

int Player::getLives() {
  return lives;
}

void Player::removeLife() {
  lives--;
}

void Player::detectCollision(SDL_Rect enemy) {

  SDL_bool collision = SDL_HasIntersection(&render, &enemy);

  if (collision) {
    Logger::warning("Colliding with the enemy!");
    removeLife();
    resetPosition();
    Logger::info("Lives: " + std::to_string(lives));
  }
}

void Player::resetPosition() {
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