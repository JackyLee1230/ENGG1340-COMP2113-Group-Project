// combatScene.h
#ifndef COMBATSCENE_H
#define COMBATSCENE_H

#include "player.h"
#include "monster.h"
#include "skill.h"

class CombatScene
{
public:
    static void playScene(Player *, Monster *);
};

#endif
