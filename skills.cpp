#include <iostream>

// for ifstream
#include <fstream>
#include <string>

// for c_str() to convert string to const char[]
#include <cstring>

// for atoi()
#include <stdlib.h>

#include "monster.h"
#include "skills.h"

// for reading xml
#include "pugixml/pugixml.hpp"

using namespace std;
using namespace pugi;

const string Monster::MONSTER_ART_FOLDER_PATH = "monsters_art/";
const char Monster::MONSTER_STATS_FILE[] = "monster_stats.xml";
const char Monster::MONSTER_SKILLS_FILE[] = "monster_skills.xml";

// constructor
Skills::Skills(int skill_ID) {
    string monster_skill_str = to_string(skill_ID);

    // get the loaded xml document
    xml_document doc;
    Skills::loadMonsterSkillsXML(doc);

    // find the specific monster with the id given
    xml_node Skills = doc.find_child_by_attribute("Skills", "id", monster_skill_str.c_str());

    // get stats and its name
    NAME = Skills.child("name").child_value();
    ATK = atoi(Skills.child("ATK").child_value());
}

int Skills::getATK() { return ATK; }

void Skills::setATK(int newATK) {
    ATK = newATK;
}

std::string Skills::getNAME() { return NAME; }


// load the xml file storing the stats of every monster
void Skills::loadMonsterSkillsXML(xml_document& doc) {
    // xml_document doc;

    // load the xml first
    xml_parse_result result = doc.load_file(MONSTER_SKILLS_FILE);

    // quick check whether we load the file successfully or not
    if (result) {
        std::cout << "XML [" << MONSTER_SKILLS_FILE << "] parsed without errors" << endl;
    }
    else {
        std::cout << "XML [" << MONSTER_SKILLS_FILE << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
        std::cout << "Error description: " << result.description() << "\n";
        std::cout << "Error offset: " << result.offset << " (error at [..." << (MONSTER_SKILLS_FILE + result.offset) << "]\n\n";
    }

    // scan all elements (don't delete, may be useful)
    // for (pugi::xml_node monster = doc.child("monster"); monster; monster = monster.next_sibling()) {
    //     cout << "Name of monster: " << monster.attribute("name").value() << endl;
    //     cout << "HP, ATK = " << monster.child("HP").child_value() << ", " << monster.child("ATK").child_value() << endl;
    // }
}
