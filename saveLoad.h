// player.h
#ifndef SAVELOAD_H
#define SAVELOAD_H

#include "pugixml/pugixml.hpp"

class SaveLoad {
  public:

    static const char PLAYER_SAVEFILE[];

    static bool checkSaveFileExist(const char*);

    static void loadSaveFile(pugi::xml_document &);

    static void saveStats();

    static void createNewSaveFile(int, int, std::string);

};

#endif