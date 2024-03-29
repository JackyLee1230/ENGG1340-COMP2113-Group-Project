// weapon.h
#ifndef WEAPON_H
#define WEAPON_H

#include "pugixml/pugixml.hpp"

#include "monster.h"

enum WeaponID {
    WOODEN_SWORD = 1,
    SOLDIER_SWORD,
    DUAL_BLADE,
    BRAVERY_BOW,
    ELDERS_WAND,
    DRAGON_HUNTER
};

// forward declaration to prevent circular depandency
class Monster;
// forward declaration ends

class Weapon {
private:

    WeaponID weapon_id;
    std::string NAME;
    int ATK;
    int CRT;
    int RANGE;
    int MAGIC;

public:

    static const char WEAPON_STATS_FILE[];

    Weapon(int);

    int getID();

    std::string getNAME();

    void setName(std::string newName);

    int getATK();

    void setATK(int);

    int getCRT();

    void setCRT(int);

    int getRANGE();

    void setRANGE(int);

    int getMAGIC();

    void setMAGIC(int);

    // to be implemented
    // the attack function
    // passing the pointer of the monster u wanna attack
    void attack(Monster *, std::string &);

    void loadWeaponXML(pugi::xml_document&);

    void showWeapon();

private:
    void dealingDmg(Monster *, std::string &);

};

#endif
