#pragma once

#include "../npc/NPC.hpp"

class Enemy : public NPC {
  private:
    void loadSprite();
    
  public:
    Enemy();

    void initialize(SDL_Renderer*);
};