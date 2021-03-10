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
        int FLOOR;


  public:

      static const char PLAYER_SAVEFILE[];

    // constructor with default value for starting a new game
    Player(bool, int newHP = 30, int newDODGE = 1, std::string newNAME = "test");

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

//     static bool checkSaveFileExist(const char*);
//
//     static void loadSaveFile(pugi::xml_document &);
//
//     static void saveStats();
//
// private:
//     void createNewSaveFile(int, int, std::string);


};

#endif
