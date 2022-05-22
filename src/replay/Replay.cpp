#include "Replay.hpp"

void Replay::initialize(SDL_Renderer* renderer) {
  Logger::okay("Initializing replay");
  this->renderer = renderer;

  map.initialize(renderer);
  player.initialize(renderer);
}

void Replay::start() {
  map.draw();
  player.draw();

  player.walking(true);
  player.autoMove();
}

void Replay::clear() {
  remove("../Replay.bin");
  std::ofstream newR("../Replay.bin", std::ios::binary);
  newR.close();
}