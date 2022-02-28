#include "Menu.hpp"

void Menu::initialize(SDL_Renderer* renderer) {
  Logger::okay("Initializing menu!");

  this->renderer = renderer;

  loadAssets();
}

void Menu::loadAssets() {
	Logger::okay("Loading the menu & selector!");

	SDL_Surface* assetBg = SDL_LoadBMP("../assets/home.bmp");
	texture = SDL_CreateTextureFromSurface(this->renderer, assetBg);
	
	SDL_Surface* assetSelector = SDL_LoadBMP("../assets/selector.bmp");
	selectorTexture = SDL_CreateTextureFromSurface(this->renderer, assetSelector);
}

void Menu::draw() {
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

	SDL_RenderCopy(
		this->renderer,
		selectorTexture,
		NULL,
		&selector
	);
}

void Menu::setSelection() {
	switch (selection) {
		case START:
			selector.y = 80;
			break;
		case LOAD_REPLAY:
			selector.y = 311;
			break;
		case QUIT:
			selector.y = 540;
			break;
	}
}

void Menu::moveDown() {
	if (selection != QUIT) {
		selection++;
	}
	setSelection();
}

void Menu::moveUp() {
	if (selection != START) {
		selection--;
	}
	setSelection();
}

int Menu::getSelection() {
	return selection;
}