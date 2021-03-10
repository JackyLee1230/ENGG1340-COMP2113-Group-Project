// player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "pugixml/pugixml.hpp"

class Player {
    private:
        int HP;
        int ATK;
        int DEF;
        std::string NAME;
        int DODGE;


  public:

      static const char PLAYER_SAVEFILE[];

    Player(bool, std::string);

    int getHP();

    void setHP(int newHP);

    int getATK();

    void setATK(int newATK);

    int getDODGE();

    void setDODGE(int newDODGE);

    // int getDEF();
    //
    // void setDEF(int newDEF);

    std::string getNAME();

    std::string setNAME(std::string newNAME);

    static void loadSaveFile(pugi::xml_document &);

    static void saveStats();

};

#endif
