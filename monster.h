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
    int SHIELDHP;
    int ATK;
    int DEF;
    std::string NAME;
    int DODGE;
    int FLIGHT;
    std::vector<Skill> skills;
    int SKILL_LOW;
    int SKILL_HIGH;
    // ShieldType shield_type;

public:
    static const std::string MONSTER_ART_FOLDER_PATH;
    // have to be char [] as the load_file() does not support string
    static const char MONSTER_STATS_FILE[];

    Monster(int);

    int getID();

    int getHP();

    void setHP(int newHP);

    int getHP_MAX();

    int getSHIELDHP();

    void setSHIELDHP(int newSHIELDHP);

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

    std::vector<Skill> getSkills();

    void setSkills(std::vector<Skill> skills);

    int getSKILLLOW();
    int getSKILLHIGH();

    void setFLIGHT(int newFLIGHT);

    std::string getNAME();

    std::string setNAME(std::string newNAME);

    void loadAsciiArt(std::string fileName);

    void loadMonsterXML(pugi::xml_document&);
};

#endif
