// monster.h
#ifndef MONSTER_H
#define MONSTER_H

#include "pugixml/pugixml.hpp"

class Monster
{
private:
    int HP;
    int ATK;
    int DEF;
    std::string NAME;
    int DODGE;
    int FLIGHT;

public:
    static const std::string MONSTER_ART_FOLDER_PATH;
    // have to be char [] as the load_file() does not support string
    static const char MONSTER_STATS_FILE[];

    Monster(int);

    int getHP();

    void setHP(int newHP);

    int getATK();

    void setATK(int newATK);

    int getDEF();

    void setDEF(int newDEF);

    int calculateHP(int HP);

    int calculateATK(float ATK);

    int calculateDEF(int DEF);

    int calculateDODGE(int DODGE);

    int getDODGE();

    void setDODGE(int newDODGE);

    int getFLIGHT();

    void setFLIGHT(int newFLIGHT);

    std::string getNAME();

    std::string setNAME(std::string newNAME);

    void loadAsciiArt(std::string fileName);

    void loadMonsterXML(pugi::xml_document&);
};

#endif
