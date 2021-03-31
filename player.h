// player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "pugixml/pugixml.hpp"
#include "weapon.h"

class Player {
    private:
        int HP;
        // int ATK;
        int DODGE;

        // game progress purpose
        int FLOOR;
        int LEVEL;

        // weapons for combat
        std::vector<Weapon> weapons;


    public:

        static const char PLAYER_SAVEFILE[];

        static const int HP_MAX;

        Player(int, int, int, int);

        int getHP();

        void setHP(int newHP);

        // int getATK();
        //
        // void setATK(int newATK);

        int getDODGE();

        void setDODGE(int newDODGE);

        int getFLOOR();

        void setFLOOR(int newFLOOR);

        int getLEVEL();

        void setLEVEL(int newLEVEL);

        void setWeapons(std::vector<Weapon>);

        std::vector<Weapon> getWeapons();

        // std::string getNAME();
        //
        // std::string setNAME(std::string newNAME);

};

#endif
