#include "Player.hpp"

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

  for (int i = 0; i < 10; i++) {
    std::string temp =  "../assets/character/" + paths[i];

    player = SDL_LoadBMP(temp.c_str());
  
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

  if (lives == 0) {
    Logger::error("Player has no lives left!");
  }
}

void Player::detectCollision(SDL_Rect npc, std::string type) {
  SDL_bool collision = SDL_HasIntersection(&render, &npc);

  if (collision) {
    if (type == "enemy") {
      Logger::warning("Colliding with the enemy!");
      removeLife();
      resetPosition();
      Logger::info("Lives: " + std::to_string(lives));
    } else if (type == "ally") {
      moveOnAllyCollide(npc);
    }
  }
}

bool Player::detectCollection(SDL_Rect animalRect, Animal *animal, std::vector<Animal*> animals) {
  SDL_bool collection = SDL_HasIntersection(&animalRect, &render);

  if (collection) {
    Logger::warning("Collecting animal");
    animals.erase(std::remove(animals.begin(), animals.end(), animal), animals.end());
    delete animal;
  }

  return collection;
}

SDL_Rect Player::getRect() {
  return this->render;
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

void Player::resetLives() {
  lives = 3;
}

void Player::moveOnAllyCollide(SDL_Rect npc) {
  if (render.x < npc.x || render.y < npc.y) {
    render.x -= speed; 
    render.y -= speed; 
  } else if (render.x > npc.x || render.y > npc.y) {
    render.x += speed; 
    render.y += speed; 
  }
}