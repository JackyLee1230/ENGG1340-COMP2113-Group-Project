#include <iostream>

// for ifstream
#include <fstream>
#include <string>

// for c_str() to convert string to const char[]
#include <cstring>

//for time for random probability
#include <time.h>

// for atoi()
#include <stdlib.h>

#include "monster.h"
#include "skill.h"
#include "player.h"
#include "monster.h"
#include "combatScene.h"
#include "SceneManager.h"

// for reading xml
#include "pugixml/pugixml.hpp"

using namespace std;
using namespace pugi;

const char Skill::MONSTER_SKILLS_FILE[] = "monster_skills.xml";

// constructor
Skill::Skill(int skill_ID) {
    string monster_skill_str = to_string(skill_ID);

    // get the loaded xml document
    xml_document doc;
    Skill::loadMonsterSkillXML(doc);

    // find the specific monster with the id given
    xml_node skill_node = doc.find_child_by_attribute("skill", "id", monster_skill_str.c_str());

    // get stats and its name
    NAME = skill_node.child("name").child_value();
    ATK = atoi(skill_node.child("ATK").child_value());
}

// member functions to get the stats of the skill that the monster casetd
int Skill::getATK() { return ATK; }

void Skill::setATK(int newATK) {
    ATK = newATK;
}

std::string Skill::getNAME() { return NAME; }


// monster damaging the player and print out the action
void Skill::act(Player *player, Monster *monster, int dmg_type, string& monster_action_des){

    switch(dmg_type){

        // pure physical damage
        case 1: {
            int player_hp = player->getHP();
            int monster_attack = this->getATK();
            player->setHP(player_hp - monster_attack);

        } break;
        // case 2: // damage to shield
            // Type type;
            // int monster_attack = monster.getATK();
            // if(monster_attack > ShieldHP){
            // }
            // break;
    }
}

// load the xml file storing the stats of every monster
void Skill::loadMonsterSkillXML(xml_document& doc) {
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
