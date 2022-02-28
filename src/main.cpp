#include "game/Game.hpp"

int main(int argv, char** args) {
	Logger::okay("Initiating game!");
	
	Game game;
	game.run();

	return 0;
}