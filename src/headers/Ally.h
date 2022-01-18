#pragma once

#include "NPC.h"

class Ally : public NPC {
  private:
    void loadSprite();
    
  public:
    Ally();

    void initialize(SDL_Renderer*);
};