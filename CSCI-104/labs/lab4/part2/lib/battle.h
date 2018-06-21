#ifndef BATTLE_H
#define BATTLE_H

#include "pokemon.h"
#include <string>
#include <iostream>

class Battle {
  public: 
    Battle(Pokemon*, Pokemon*);
    void run();

  private:
    Pokemon *playerA, *playerB;
    bool playerAturn;
};

#endif