// skills.h
#ifndef SKILL_H
#define SKILL_H

#include "pugixml/pugixml.hpp"
#include "monster.h"
#include "player.h"

enum Type {
	damage,
	shield
};

class SKILL
{
private:
    int ATK;
    int dmg;
    bool isMagic;
    std::string NAME;
    int dmg_type;
    Type type;


public:

    static const std::string MONSTER_ART_FOLDER_PATH;
    // have to be char [] as the load_file() does not support string
    static const char MONSTER_STATS_FILE[];
    static const char MONSTER_SKILLS_FILE[];

    int getATK();

    void setATK(int newATK);

    std::string getNAME();

    void loadMonsterXML(pugi::xml_document&);

    void act(Player player, Monster monster);

    void attack(Player player, Monster monster, int damage);
};

#endif
