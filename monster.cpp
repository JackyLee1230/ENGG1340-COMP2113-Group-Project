#include <iostream>
#include <vector>

// for ifstream
#include <fstream>
#include <string>

// for c_str() to convert string to const char[]
#include <cstring>

// for atoi()
#include <stdlib.h>

#include "monster.h"
#include "skill.h"
#include "player.h"

// for reading xml
#include "pugixml/pugixml.hpp"

using namespace std;
using namespace pugi;

const string Monster::MONSTER_ART_FOLDER_PATH = "monsters_art/";
const char Monster::MONSTER_STATS_FILE[] = "monster_stats.xml";

// constructor
// construct a monster given its ID in the xml file
// have to use const char* to match with the child() function
Monster::Monster(int monster_ID) {
    this->ID = monster_ID;

    string monster_ID_str = to_string(monster_ID);

    // get the loaded xml document
    xml_document doc;
    Monster::loadMonsterXML(doc);

    // find the specific monster with the id given
    xml_node monster = doc.find_child_by_attribute("monster", "id", monster_ID_str.c_str());

    // get stats and its name
    NAME = monster.child("name").child_value();
    HP = atoi(monster.child("HP").child_value());
    HP_MAX = HP;
    SHIELDHP = 0;
    ATK = atoi(monster.child("ATK").child_value());
    DEF = atoi(monster.child("DEF").child_value());
    DODGE = atoi(monster.child("DODGE").child_value());
    FLIGHT = atoi(monster.child("FLIGHT").child_value());
    SKILL_LOW = atoi(monster.child("SKILL_LOW").child_value());
    SKILL_HIGH = atoi(monster.child("SKILL_HIGH").child_value());

    // initialize the skill set of the monster
    // Improve performance in combat scene (w/out the need to read xml repeatly)
    this->skills.clear();

    for (int i = SKILL_LOW; i <= SKILL_HIGH; i++) {
        Skill skill = Skill(i);
        this->skills.push_back(skill);
    }
}


//member functions to set the stats of the monster and return the value when needed
int Monster::getID() { return this->ID; }

int Monster::getHP() { return HP; }

void Monster::setHP(int newHP) {
    HP = newHP;
}

int Monster::getHP_MAX() { return HP_MAX; }

int Monster::getSHIELDHP() { return this->SHIELDHP; }

void Monster::setSHIELDHP(int newSHIELDHP) {
    this->SHIELDHP = newSHIELDHP;
}

int Monster::getATK() { return ATK; }

void Monster::setATK(int newATK) {
    ATK = newATK;
}

int Monster::getDODGE() { return DODGE; }

void Monster::setDODGE(int newDODGE) {
    DODGE = newDODGE;
}

int Monster::getFLIGHT() { return FLIGHT; }

void Monster::setFLIGHT(int newFLIGHT){
    FLIGHT = newFLIGHT;
}

int Monster::getSKILLLOW() { return SKILL_LOW; }

int Monster::getSKILLHIGH() { return SKILL_HIGH; }

int Monster::getDEF() { return DEF; }

void Monster::setDEF(int newDEF){
    DEF = newDEF;
}

std::string Monster::getNAME() { return NAME; }

std::string Monster::setNAME(std::string newNAME){
    NAME = newNAME;
}

std::vector<Skill> Monster::getSkills() { return this->skills; }

void Monster::setSkills(std::vector<Skill> newSkills) {
    this->skills = newSkills;
}

// int Monster::calculateHP(int HP){
//     return float(HP) * level * 1.3;
// }
//
// int Monster::calculateATK(float ATK){
//     return float(ATK) * level * 1.3;
// }
//
// int Monster::calculateDEF(int DEF){
//     return float(DEF) * level * 1.3;
// }

// print the monster art
// similar to loadTitleScreen
void Monster::loadAsciiArt(string fileName) {
    string file_name = fileName + ".txt";
    string line;

    ifstream myfile (MONSTER_ART_FOLDER_PATH + file_name);

    // load the specific scene only
    if (myfile.is_open()) {
        while (getline (myfile, line)) {
            cout << line << '\n';
        }
        cout << endl;
    }

    myfile.close();
}

// load the xml file storing the stats of every monster
void Monster::loadMonsterXML(xml_document& doc) {
    // xml_document doc;

    // load the xml first
    xml_parse_result result = doc.load_file(MONSTER_STATS_FILE);

    // quick check whether we load the file successfully or not
    if (result) {
        std::cout << "XML [" << MONSTER_STATS_FILE << "] parsed without errors" << endl;
    }
    else {
        std::cout << "XML [" << MONSTER_STATS_FILE << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
        std::cout << "Error description: " << result.description() << "\n";
        std::cout << "Error offset: " << result.offset << " (error at [..." << (MONSTER_STATS_FILE + result.offset) << "]\n\n";
    }

    // scan all elements (don't delete, may be useful)
    // for (pugi::xml_node monster = doc.child("monster"); monster; monster = monster.next_sibling()) {
    //     cout << "Name of monster: " << monster.attribute("name").value() << endl;
    //     cout << "HP, ATK = " << monster.child("HP").child_value() << ", " << monster.child("ATK").child_value() << endl;
    // }
}
