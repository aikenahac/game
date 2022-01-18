#pragma once

#include "NPC.h"

class Enemy : public NPC {
  private:
    void loadSprite();
    
  public:
    Enemy();

    void initialize(SDL_Renderer*);
};