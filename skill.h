// skills.h
#ifndef SKILL_H
#define SKILL_H

#include "pugixml/pugixml.hpp"
#include "player.h"
#include "monster.h"

enum Type {
	DAMAGE = 0,
	SHIELD
};

// forward declaration to prevent circular depandency
class Player;
class Monster;
// forward declaration ends

class Skill
{
private:
	std::string NAME;
    int ATK;
    bool isMagic;
    Type type;


public:
    static const char MONSTER_SKILLS_FILE[];

	Skill(int);

    int getATK();

    void setATK(int newATK);

    std::string getNAME();

	Type getType();

    void loadMonsterSkillXML(pugi::xml_document&);

    void act(Player *player, Monster *monster, std::string &);

//    void attack(Player *player, Monster *monster, int damage);
};

#endif
