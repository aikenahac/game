#include "Leaderboard.hpp"

void Leaderboard::initialize(SDL_Renderer* renderer) {
  Logger::okay("Initializing leaderboard!");

  this->renderer = renderer;

  loadAssets();
}

void Leaderboard::loadAssets() {
	Logger::okay("Loading the menu & selector!");

	SDL_Surface* assetBg = SDL_LoadBMP("../assets/leaderboard_bg.bmp");
	texture = SDL_CreateTextureFromSurface(this->renderer, assetBg);

}

void Leaderboard::loadScores() {
  std::ifstream data("../Leaderboard.bin", std::ios::binary);

  Save curr;

  if (data.is_open()) {
		int ctr = 0;

  	while (data.read((char *) &curr, sizeof(Save))) {
			char player[100];
			std::strcpy(player, curr.player);
			
			char score[4];
			std::strcpy(score, std::to_string(curr.score).c_str());

			char* message = new char[std::strlen(player) + std::strlen(score) + 2];
	
			std::strcpy(message, player);
			std::strcat(message, ": ");
			std::strcat(message, score);

			std::cout << message << "\n";

			Utils::renderText(renderer, 400, 200 + ctr * 50, message, 64);

			ctr++;
		}
	}

  data.close();
}

void Leaderboard::draw() {
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
  
  this->loadScores();
}