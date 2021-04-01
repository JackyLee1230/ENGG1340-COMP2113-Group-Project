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

class Skill
{
private:
    int ATK;
    int dmg;
    bool isMagic;
    std::string NAME;
    int dmg_type;
    Type type;


public:
    static const char MONSTER_SKILLS_FILE[];

	Skill(int);

    int getATK();

    void setATK(int newATK);

    std::string getNAME();

    void loadMonsterSkillXML(pugi::xml_document&);

    void act(Player *player, Monster *monster, Skill *skill ,int dmg_type);

//    void attack(Player *player, Monster *monster, int damage);
};

#endif
