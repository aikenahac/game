#pragma once

#include "../npc/NPC.hpp"

class Ally : public NPC {
  private:
    void loadSprite();
    
  public:
    Ally();

    void initialize(SDL_Renderer*);
};