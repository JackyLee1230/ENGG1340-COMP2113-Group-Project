// monster.h
#ifndef MONSTER_H
#define MONSTER_H

#include <vector>
#include <string>

#include "pugixml/pugixml.hpp"
#include "skill.h"


// //enum for monster shield
// enum ShieldType {
//      shieldless,
//      phy_shield,
//      magic_shield
// };


class Monster
{
private:
    int ID;
    int HP;
    int HP_MAX;
    int ATK;
    std::string NAME;
    int DODGE;
    int FLIGHT;

    // skills part
    std::vector<Skill> skills;
    int SKILL_LOW;
    int SKILL_HIGH;
    int WEAPON_DROP;

    // shields part
    int SHIELDHP;
    bool SHIELD_ISMAGIC;

    // flight part
    bool isFlying;
    int flight_rounds;

public:
    static const std::string MONSTER_ART_FOLDER_PATH;
    // have to be char [] as the load_file() does not support string
    static const char MONSTER_STATS_FILE[];

    Monster(int);

    int getID();

    int getHP();

    void setHP(int newHP);

    int getHP_MAX();

    int getATK();

    void setATK(int newATK);

    int getWEAPONDROP();

    // shield part
    int getSHIELDHP();

    void setSHIELDHP(int newSHIELDHP);

    bool getSHIELD_ISMAGIC();

    void setSHIELD_ISMAGIC(bool);

    int calculateDODGE(int DODGE);

    int getDODGE();

    void setDODGE(int newDODGE);

    // Flight part
    int getFLIGHT();

    void setFLIGHT(int newFLIGHT);

    bool getIsFlying();

    int fly();

    std::vector<Skill> getSkills();

    void setSkills(std::vector<Skill> skills);

    int getSKILLLOW();
    int getSKILLHIGH();

    std::string getNAME();

    std::string setNAME(std::string newNAME);

    void loadAsciiArt(std::string fileName);

    void loadMonsterXML(pugi::xml_document&);
};

#endif
