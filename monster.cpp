#include <iostream>
#include <vector>

// for ifstream
#include <fstream>
#include <string>

// for c_str() to convert string to const char[]
#include <cstring>

// for atoi()
#include <stdlib.h>

// for log()
#include <cmath>

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
// Input: accept monster ID
// Output: construct a monster given its ID in the xml file and save its stats
// also get the skills of the monsters

// have to use const char* to match with the child() function
Monster::Monster(int monster_ID) {
    this->ID = monster_ID;

    string monster_ID_str = to_string(monster_ID);

    // get the loaded xml document
    xml_document doc;
    Monster::loadMonsterXML(doc);

    // find the specific monster with the id given
    xml_node monster = doc.find_child_by_attribute("monster", "id", monster_ID_str.c_str());

    // get stats and its name from XML
    NAME = monster.child("name").child_value();
    HP = atoi(monster.child("HP").child_value());
    HP_MAX = HP;
    ATK = atoi(monster.child("ATK").child_value());
    DODGE = atoi(monster.child("DODGE").child_value());
    FLIGHT = atoi(monster.child("FLIGHT").child_value());
    SKILL_LOW = atoi(monster.child("SKILL_LOW").child_value());
    SKILL_HIGH = atoi(monster.child("SKILL_HIGH").child_value());
    WEAPON_DROP = atoi(monster.child("WEAPON_DROP").child_value());

    // shield stuff
    SHIELDHP = 0;
    SHIELD_ISMAGIC = false;

    // flight stuff
    this->isFlying = false;
    this->flight_rounds = 0;

    // initialize the skill set of the monster
    // Improve performance in combat scene (w/out the need to read xml repeatly)
    this->skills.clear();

    for (int i = SKILL_LOW; i <= SKILL_HIGH; i++) {
        Skill skill = Skill(i);
        this->skills.push_back(skill);
    }
}


//member functions to set the stats of the monster and return the value when needed

// Output: Monster's ID
int Monster::getID() { return this->ID; }

// Output: Monster's HP
int Monster::getHP() { return HP; }

// Input: new Monster's HP
// Output: Update Monster's HP
void Monster::setHP(int newHP) {
    HP = newHP;
}

// Output: Monster's Max HP
int Monster::getHP_MAX() { return HP_MAX; }

// Output: Monster's Attack
int Monster::getATK() { return ATK; }

// Input: new Monster's Attack
// Output: Update Monster's Attack
void Monster::setATK(int newATK) {
    ATK = newATK;
}

// Output: Monster's Dodge
int Monster::getDODGE() { return DODGE; }

// Input: new Monster's Dodge
// Output: Update Monster's Dodge
void Monster::setDODGE(int newDODGE) {
    DODGE = newDODGE;
}

// Output: Monster's Flight Mode
int Monster::getFLIGHT() { return FLIGHT; }

// Input: Set Monster's Flight Mode
void Monster::setFLIGHT(int newFLIGHT){
    FLIGHT = newFLIGHT;
}

// Output: Monster's Skill Lower and Upper bound
int Monster::getSKILLLOW() { return SKILL_LOW; }
int Monster::getSKILLHIGH() { return SKILL_HIGH; }

// shield part

// Output: Monster's Shield HP
int Monster::getSHIELDHP() { return this->SHIELDHP; }

// Input: new Monster's Shield HP
// Output: Update Monster's Shield HP
void Monster::setSHIELDHP(int newSHIELDHP) {
    this->SHIELDHP = newSHIELDHP;
}

// Output: Whether Shield is a magic shield
bool Monster::getSHIELD_ISMAGIC() { return this->SHIELD_ISMAGIC; }

// Input: set Monster's shield to be magic or not
void Monster::setSHIELD_ISMAGIC(bool isMagic) {
    this->SHIELD_ISMAGIC = isMagic;
}

// Output: ID of Monster's Weapon Drop
int Monster::getWEAPONDROP() { return WEAPON_DROP; }

// Output: Monster's Name
std::string Monster::getNAME() { return NAME; }

// Input: Set Monster's Name
std::string Monster::setNAME(std::string newNAME){
    NAME = newNAME;
}

// Output: vector of Monster's Skills
std::vector<Skill> Monster::getSkills() { return this->skills; }

// Input: vector of Skills
// set the skills of a monster using a vector
void Monster::setSkills(std::vector<Skill> newSkills) {
    this->skills = newSkills;
}

// Output: Whether Monster is Flying
bool Monster::getIsFlying() { return this->isFlying; }

// flight stuff
// Input: -
// Output: whether the monster is currently flying and how many rounds it has been flying
// maths functions to decide when the monster gets down on the ground
int Monster::fly() {
    if (!isFlying) {
        // generate probability to decide whether the monster wants to fly
        double flight_prob = 0.3;
        double flight_roll = (double) (rand() / (RAND_MAX + 1.0));
        bool toFly = flight_prob > flight_roll ? true : false;

        if (toFly) {
            isFlying = true;
            flight_rounds = 0;
            flight_rounds++;

            // return the result to generate corresponding sentences
            return 1;
        }
    }
    else {
        // generate probabiity to decide whether the monster wants to land
        // landing prob will increase with number of isFlying turns
        // use log function to generate probabiity
        double land_prob = log10(flight_rounds);
        double land_roll = (double) (rand() / (RAND_MAX + 1.0));
        bool toLand = land_prob > land_roll ? true : false;

        if (toLand) {
            isFlying = false;
            flight_rounds = 0;

            // return the result to generate corresponding sentences
            return -1;
        }
        else {
            flight_rounds++;
        }
    }

    return 0;
}

//Input: -
//Output: Return string of whether the monster is flying or not to the combat scene
string Monster::getFlightDescription() {

    string flight_description = "";

    if (this->isFlying) {
        flight_description = this->getNAME() + " is flying !!" + "\n";
    }
    else {
        flight_description = this->getNAME() + " is on ground !!" + "\n";
    }

    return flight_description;
}

// Input: the name of the file to be print
// Output: print the monster art from the file
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

// Input: Monster Stats XML File
// Output: load the xml file storing the stats of every monster
void Monster::loadMonsterXML(xml_document& doc) {
    // xml_document doc;

    // load the xml first
    xml_parse_result result = doc.load_file(MONSTER_STATS_FILE);

    // quick check whether we load the file successfully or not
    // if (result) {
    //     std::cout << "XML [" << MONSTER_STATS_FILE << "] parsed without errors" << endl;
    // }
    // else {
    //     std::cout << "XML [" << MONSTER_STATS_FILE << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
    //     std::cout << "Error description: " << result.description() << "\n";
    //     std::cout << "Error offset: " << result.offset << " (error at [..." << (MONSTER_STATS_FILE + result.offset) << "]\n\n";
    // }
}
