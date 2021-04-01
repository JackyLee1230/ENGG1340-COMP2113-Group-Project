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

int Weapon::getID() {
    return static_cast<int>(this->weapon_id);
}

string Weapon::getNAME() { return this->NAME; }

int Weapon::getATK() { return this->ATK; }

int Weapon::getCRT() { return this->CRT; }

int Weapon::getRANGE() { return this->RANGE; }

int Weapon::getMAGIC() { return this->MAGIC; }

void Weapon::attack(Monster *monster){
    int damage = this->ATK;
    srand(unsigned(time(NULL))); // random prob using time
    double dodge_prob = monster->getDODGE() / 100;// probability of dodge depend on the monster
    double roll = (double) (rand() / (RAND_MAX + 1.0)); //generate rand prob with time
    if(roll > dodge_prob){
        if(monster->getHP() > damage){
            // reduce HP by dmg value
            monster->setHP(monster->getHP() - damage);
        }else if(monster->getHP() == damage){
            monster->setHP(0);
            cout << "You barely defeated the Monster and it fainted." << endl;
        }else if(damage > monster->getHP()){
            // set HP to 0 since player damage is higher than monster health
            monster->setHP(0);
        }
    }else{
        cout << "The Monster were quick enough to realised and evaded your attack!!!!" << endl;
        monster->setHP(monster->getHP());
    }
}

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

void Weapon::showWeapon() {
    // output weapon stats depened on whether it is a
    // magic / range / normal type weapon
    if(this->RANGE == 1){
        if(this->MAGIC == 1){
            fprintf(stdout, "%-16s%4s< ATK: %2d, CRT: %2d%, RANGE: TRUE, MAGIC: TRUE >",
                this->NAME.c_str(),
                "",
                this->ATK,
                this->CRT
            );
        }else {
            fprintf(stdout, "%-16s%4s< ATK: %2d, CRT: %2d%, RANGE: TRUE >",
                this->NAME.c_str(),
                "",
                this->ATK,
                this->CRT
            );
        }
    }
    else{
        fprintf(stdout, "%-16s%4s< ATK: %2d, CRT: %2d% >",
            this->NAME.c_str(),
            "",
            this->ATK,
            this->CRT
        );
    }

}
