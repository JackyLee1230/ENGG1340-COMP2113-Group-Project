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
    srand(unsigned(time(NULL))); // random prob using time
    double crt_chance = this->CRT / 100; // get crt chance from weapon stats
    double crt_roll = (double) (rand() / (RAND_MAX + 1.0)); // generate rand prob with time'

    //seed the random again, so that the roll of crit and dodge will not be the same
    srand(unsigned(time(NULL)));
    double dodge_prob = monster->getDODGE() / 100;// probability of dodge depend on the monster
    double dodge_roll = (double) (rand() / (RAND_MAX + 1.0)); //generate rand prob with time

    bool isDodged =  dodge_roll > dodge_prob ? false : true;
    bool isCritical = crt_chance > crt_roll ? true : false;

    int damage_fin = this->getATK();

    // check according to the following sequence
    // 1. weapon type (physical or magical)
    // 2. dodge
    // 3. shield
    // 4. critical dmg

    if (isDodged) {
        player_action_des = "The Monster were quick enough to realised and evaded your attack!!!!";

        // when the attack is dodged, no damage will be dealt to the monster
        monster->setHP(monster->getHP());
    }
    else {
        // if a critical attack is dealt
        if (isCritical) {
            // critical attack
            damage_fin *= 2;
            player_action_des = "You dealt a critical hit and dealt 2 times damage \n";
        }

        // hit on the shield
        if (monster->getSHIELDHP() > 0) {
            monster->setSHIELDHP(monster->getSHIELDHP() - damage_fin);

            // extra damage has been dealt to the monster's shield
            // remaining damage will be dealt to the HP itself
            if (monster->getSHIELDHP() < 0) {
                monster->setHP(monster->getHP() + monster->getSHIELDHP());
                monster->setSHIELDHP(0);
            }
        }
        else {
            // normal attack
            monster->setHP(monster->getHP() - damage_fin);
        }

        player_action_des += "Using " + string(this->NAME) +  " to attack and dealt " + to_string(damage_fin) + " damage to " + monster->getNAME() + "!" ;

        // barely defeated the monster
        if (monster->getHP() == 0) {
            player_action_des += "\nYou barely defeated the Monster and it died.";
        }
        // defeated the monster
        else if (monster->getHP() < 0) {
            player_action_des += "\nYou destroyed the Monster!!";
        }

    }
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
            fprintf(stdout, "%-16s%4s< ATK: %2d, CRT: %2d%, RANGE: TRUE, MAGIC: TRUE >",
                this->NAME.c_str(),
                "",
                this->ATK,
                this->CRT
            );
        }else { // weapon is ranged
            fprintf(stdout, "%-16s%4s< ATK: %2d, CRT: %2d%, RANGE: TRUE >",
                this->NAME.c_str(),
                "",
                this->ATK,
                this->CRT
            );
        }
    }
    else{ // weapon only deals physical damage
        fprintf(stdout, "%-16s%4s< ATK: %2d, CRT: %2d% >",
            this->NAME.c_str(),
            "",
            this->ATK,
            this->CRT
        );
    }

}
