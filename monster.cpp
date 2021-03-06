#include <iostream>

// for ifstream
#include <fstream>
#include <string>

// for atoi()
#include <stdlib.h>

#include "monster.h"

// for reading xml
#include "pugixml/pugixml.cpp"

using namespace std;
using namespace pugi;

const string Monster::MONSTER_ART_FOLDER_PATH = "monsters_art/";
const char Monster::MONSTER_STATS_FILE[] = "monster_stats.xml";

// constructor
// construct a monster given its name in the xml file
// have to use const char* to match with the child() function
Monster::Monster(const char* monster_name) {
    string monster_name_str(monster_name);

    // get the loaded xml document
    xml_document doc;
    Monster::loadMonsterStats(doc);

    // find the specific monster with the name given
    xml_node monster = doc.find_child_by_attribute("monster", "name", monster_name);

    // set stats
    NAME = monster_name_str;
    HP = atoi(monster.child("HP").child_value());
    ATK = atoi(monster.child("ATK").child_value());
    DEF = atoi(monster.child("DEF").child_value());
}

int Monster::getHP() { return HP; }

void Monster::setHP(int newHP) {
    HP = newHP;
}

int Monster::getATK() { return ATK; }

void Monster::setATK(int newATK) {
    ATK = newATK;
}

int Monster::getDEF() { return DEF; }

void Monster::setDEF(int newDEF){
    DEF = newDEF;
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

std::string Monster::getNAME() { return NAME; }

std::string Monster::setNAME(std::string newNAME){
    NAME = newNAME;
}

// load the monster art
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

// load the stats of the monster from a xml file
// provided the name of the monster
void Monster::loadMonsterStats(xml_document& doc) {

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
