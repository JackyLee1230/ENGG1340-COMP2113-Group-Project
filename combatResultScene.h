// combatResultScene
#ifndef COMBATRESULTSCENE_H
#define COMBATRESULTSCENE_H

#include "player.h"
#include "monster.h"

class CombatResultScene {
public:
    static void playScene(Player *, Monster *, bool);
};

#endif
