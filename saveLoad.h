// saveLoad.h
#ifndef SAVELOAD_H
#define SAVELOAD_H

#include "pugixml/pugixml.hpp"

#include "player.h"
#include "weapon.h"

class SaveLoad {
public:

    static const char PLAYER_SAVEFILE[];

    static bool checkSaveFileExist();

    static Player* loadSaveFile();

    static void saveStats(Player *);

    static void createNewSaveFile(Player*);

    static std::vector<Weapon> loadPlayerWeapons(pugi::xml_node);
    static std::vector<Fruit> loadPlayerFruits(pugi::xml_node);
};

#endif
