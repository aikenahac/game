#include "game/Game.hpp"

int main(int argv, const char *args[]) {
	Logger::okay("Initiating game!");

	bool fullscreen = 0;
	std::cout << "Start game in fullscreen? [0 - no/1 - yes]: ";
	std::cin >> fullscreen;


	Game game = Game(fullscreen);
	game.run();

	return 0;
}