#include "NPC.hpp"

void NPC::draw() {
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

void NPC::setDirection(uint8_t direction) {
  this->direction = direction;
}

void NPC::walking(bool isWalking) {
  this->isWalking = isWalking;
}

SDL_Rect NPC::getRect() {
  return render;
}

void NPC::detectCollision(SDL_Rect enemy) {

  SDL_bool collision = SDL_HasIntersection(&render, &enemy);

  if (collision) {
    dead = true;
  }
}

void NPC::movement(SDL_Rect target) {
  if (dead) return;


  SDL_Rect temp = {
    target.x,
    target.y
  };

  std::cout << "x: " << temp.x << ", y: " << temp.y << "\n";
  
  if (!this->compareRect(temp)) {
    if (render.x > temp.x && render.y > temp.y) {
      moveLeft();
      moveUp();
    } else if (render.x < temp.x && render.y > temp.y) {
      moveUp();
      moveRight();
    } else if (render.x > temp.x && render.y < temp.y) {
      moveDown();
      moveLeft();
    } else if (render.x < temp.x && render.y < temp.y) {
      moveDown();
      moveRight();
    }
  }
}

void NPC::detectBorderCollision() {
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

void NPC::moveUp() {
  this->setDirection(3);
  this->walking(true);

  this->render.y -= speed;
  detectBorderCollision();
}

void NPC::moveDown() {
  this->setDirection(0);
  this->walking(true);

  this->render.y += speed;
  detectBorderCollision();
}

void NPC::moveLeft() {
  this->setDirection(6);
  this->walking(true);

  this->render.x -= speed;
  detectBorderCollision();
}

void NPC::moveRight() {
  this->setDirection(8);
  this->walking(true);

  this->render.x += speed;
  detectBorderCollision();
}

bool NPC::compareRect(SDL_Rect temp) {
  if (render.x == temp.x && render.y == temp.y) return true;
  return false;
}