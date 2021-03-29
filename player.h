// player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "pugixml/pugixml.hpp"

class Player {
    private:
        int HP;
        int ATK;
        int DEF;
        int DODGE;
        int FLOOR;

  public:

      static const char PLAYER_SAVEFILE[];

      static const int HP_MAX;

    Player(int, int, int);

    int getHP();

    void setHP(int newHP);

    int getATK();

    void setATK(int newATK);

    int getDODGE();

    void setDODGE(int newDODGE);

    int getFLOOR();

    void setFLOOR(int newFLOOR);

    // int getDEF();
    //
    // void setDEF(int newDEF);

    std::string getNAME();

    std::string setNAME(std::string newNAME);

};

#endif
