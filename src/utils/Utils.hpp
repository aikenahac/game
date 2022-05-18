#pragma once

#include <sstream>
#include <SDL2/SDL_ttf.h>

struct Save {
  char player[100];
  int score;
};

class Utils {
  public:
    static void renderText(
      SDL_Renderer *renderer,
      int x,
      int y,
      char text[],
      int size
    );

    static std::string convertToString(char str[]);
};