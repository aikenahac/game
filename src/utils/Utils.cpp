#include "Utils.hpp"

void Utils::renderText(SDL_Renderer *renderer, int x, int y, char text[], int size) {
  TTF_Font *robotoMono = TTF_OpenFont("../assets/fonts/roboto_mono.ttf", size);
  SDL_Surface *surface = TTF_RenderText_Solid(robotoMono, text, {255, 255, 255});

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_Rect render {
    x,
    y,
    surface->w,
    surface->h,
  };

  SDL_RenderCopy(renderer, texture, nullptr, &render);

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);

  TTF_CloseFont(robotoMono);
}

std::string Utils::convertToString(char str[]) {
  int size = sizeof(str) / sizeof(char);

  std::string s = "";

  for (int i = 0; i < size; i++) {
    s += str[i];
  }

  return s;
}