#include <iostream>
#include <string>

// for atoi()
#include <stdlib.h>

// for fprintf()
#include <cstdio>

// for c_str() to convert string to const char[]
#include <cstring>

#include "pugixml/pugixml.hpp"
#include "weapon.h"
#include "player.h"
#include "monster.h"

using namespace std;
using namespace pugi;

const char Weapon::WEAPON_STATS_FILE[] = "weapon_stats.xml";

// constructor to initialize weapon using weapon ID
Weapon::Weapon(int weaponID) {

    // load the weapon's stats from xml doc
    xml_document doc;
    Weapon::loadWeaponXML(doc);

    // get the weapon that we wanna load
    xml_node weapon = doc.find_child_by_attribute("weapon", "id", to_string(weaponID).c_str());

    // get stats and others
    weapon_id = static_cast<WeaponID>(weaponID);
    NAME = weapon.child("name").child_value();
    ATK = atoi(weapon.child("ATK").child_value());
    CRT = atoi(weapon.child("CRT").child_value());
    RANGE = atoi(weapon.child("RANGE").child_value());
    MAGIC = atoi(weapon.child("MAGIC").child_value());
}
// member functions that return the stats of the weapon
int Weapon::getID() {
    return static_cast<int>(this->weapon_id);
}

string Weapon::getNAME() { return this->NAME; }

int Weapon::getATK() { return this->ATK; }

int Weapon::getCRT() { return this->CRT; }

int Weapon::getRANGE() { return this->RANGE; }

int Weapon::getMAGIC() { return this->MAGIC; }

// function for Player to attack monster using the specificed weapon
// and have a chacne of critical hit and a chance of the monster dodging the attack
void Weapon::attack(Monster *monster, string& player_action_des){

    //seed the random again, so that the roll of crit and dodge will not be the same
    srand(unsigned(time(NULL)));
    double dodge_prob = monster->getDODGE() / 100;// probability of dodge depend on the monster
    double dodge_roll = (double) (rand() / (RAND_MAX + 1.0)); //generate rand prob with time

    bool isDodged =  dodge_prob >  dodge_roll ? true : false;

    // check according to the following sequence
    // 1. weapon type (physical or magical)
    // 2. dodge
    // 3. critical dmg  (in dealing dmg)
    // 4. shield    (in dealing dmg)

    // first check
    // set dodged to false
    if (this->getMAGIC())
        isDodged = false;

    // second check (pt 1)
    // check whether the monster is flying
    // and the player is using a non-ranged weapon
    else if (monster->getIsFlying() && this->getRANGE() == false)
        isDodged = true;

    // second check (pt 2)
    if (isDodged) {
        player_action_des = monster->getNAME() + " was quick enough to realised and evaded your attack!!!!\n";

        // when the attack is dodged, no damage will be dealt to the monster
        monster->setHP(monster->getHP());
    }
    else {
        switch(this->weapon_id) {
            // weapons that attack twice in a row
            case WeaponID::DUAL_BLADE:
            case WeaponID::DRAGON_HUNTER: {
                // our dmg dealing function
                dealingDmg(monster, player_action_des);
                dealingDmg(monster, player_action_des);
            }
            break;
            default:
                // if it is not the two above, then only hit once
                // our dmg dealing function
                dealingDmg(monster, player_action_des);
        }

         // show when player use a magic weapon
        if(this->getMAGIC() == 1){
            player_action_des += "You used a Magic Weapon and the Monster could not evade the attack!\n";
        }

        // barely defeated the monster
        if (monster->getHP() == 0) {
            player_action_des += "You barely defeated the Monster and it died.\n";
        }
        // defeated the monster
        else if (monster->getHP() < 0) {
            player_action_des += "You destroyed the Monster!!\n";
        }
    }
}

// dealing damage function
// return the damage deal to the HP of the monster (not the shield one)
// which will be shown on scene message
void Weapon::dealingDmg(Monster *monster, string& player_action_des) {
    // our damage
    int damage_fin = this->getATK();
    int damage_display = damage_fin;

    srand(unsigned(time(NULL))); // random prob using time
    double crt_chance = this->CRT / 100; // get crt chance from weapon stats
    double crt_roll = (double) (rand() / (RAND_MAX + 1.0)); // generate rand prob with time'

    bool isCritical = crt_chance > crt_roll ? true : false;

    // third check
    // if a critical attack is dealt
    if (isCritical) {
        // critical attack , deal 2 times the damage
        damage_fin *= 2;
        player_action_des = "You dealt a critical hit and dealt 2 times damage \n";
    }

    // our last check
    // check whether there is a shield and the attack is same type of the shield
    // not the same type --> break the shield directly
    if (monster->getSHIELDHP() > 0
        && this->getMAGIC() != monster->getSHIELD_ISMAGIC()) {
            player_action_des += "You break the shield!!!\n";
            monster->setSHIELDHP(0);
    }

    // check again, whether the shield is broken
    // run if the shield is not broken
    if (monster->getSHIELDHP() > 0) {

        monster->setSHIELDHP(monster->getSHIELDHP() - damage_fin);

        // extra damage has been dealt to the monster's shield
        // remaining damage will be dealt to the HP itself
        if (monster->getSHIELDHP() < 0) {

            player_action_des += "You broke the shield of the monster!!!\n";

            monster->setHP(monster->getHP() + monster->getSHIELDHP());

            damage_display = -monster->getSHIELDHP();

            monster->setSHIELDHP(0);
        }
    }
    // not hitting on shield , directly damage the monster
    else {
        monster->setHP(monster->getHP() - damage_fin);
    }

    // showing the damage on screen
    player_action_des += "Using " + this->getNAME() +  " to attack and dealt " + to_string(damage_display) + " damage to " + monster->getNAME() + "!" + "\n" ;
}

// load the weapon stats from the weapon_stats XML file
// output whether there is an error or not in reading the stats
void Weapon::loadWeaponXML(xml_document& doc) {
    // load the xml first
    xml_parse_result result = doc.load_file(WEAPON_STATS_FILE);

    // quick check whether we load the file successfully or not
    if (result) {
        std::cout << "XML [" << WEAPON_STATS_FILE << "] parsed without errors" << endl;
    }
    else {
        std::cout << "XML [" << WEAPON_STATS_FILE << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
        std::cout << "Error description: " << result.description() << "\n";
        std::cout << "Error offset: " << result.offset << " (error at [..." << (WEAPON_STATS_FILE + result.offset) << "]\n\n";
    }
}

//using a loop, and depending on the weapon Type
//print out the weapon in different format
// including NAME, ATK, CRT, RANGE, MAGIC
void Weapon::showWeapon() {
    // output weapon stats depened on whether it is a
    // magic / range / normal type weapon
    if(this->RANGE == 1){
        if(this->MAGIC == 1){ // weapon is ranged and does magic damage
            fprintf(stdout, "%-16s%4s< ATK: %2d, CRT: %2d%, RANGE: TRUE, MAGIC: TRUE >\n",
                this->NAME.c_str(),
                "",
                this->ATK,
                this->CRT
            );
        }else { // weapon is ranged
            fprintf(stdout, "%-16s%4s< ATK: %2d, CRT: %2d%, RANGE: TRUE >\n",
                this->NAME.c_str(),
                "",
                this->ATK,
                this->CRT
            );
        }
    }
    else{ // weapon only deals physical damage
        fprintf(stdout, "%-16s%4s< ATK: %2d, CRT: %2d% >\n",
            this->NAME.c_str(),
            "",
            this->ATK,
            this->CRT
        );
    }

    // showing that some weapons can attack twice in a row (their special ability)
    switch (this->weapon_id) {
        case DUAL_BLADE:
        case DRAGON_HUNTER:
            fprintf(stdout, "%4s%-16s%4s< Attacked TWICE in a round >\n",
                "", "", "");
            break;
    }

}
