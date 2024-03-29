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
#include "sceneManager.h"

// for reading xml
#include "pugixml/pugixml.hpp"

using namespace std;
using namespace pugi;

const char Skill::MONSTER_SKILLS_FILE[] = "monster_skills.xml";

// constructor
// Input: accept Skill ID
// Output: construct a Skill obj with stats from the XML file
Skill::Skill(int skill_ID) {
    string monster_skill_str = to_string(skill_ID);

    // get the loaded xml document
    xml_document doc;
    Skill::loadMonsterSkillXML(doc);

    // find the specific monster with the id given
    xml_node skill_node = doc.find_child_by_attribute("skill", "id", monster_skill_str.c_str());

    // get stats and its name
    this->NAME = skill_node.child("name").child_value();
    this->type = static_cast<Type>(atoi(skill_node.child("type").child_value()));
    this->ATK = atoi(skill_node.child("ATK").child_value());
    this->isMagic = atoi(skill_node.child("isMagic").child_value());
}

// member functions to get the stats of the skill that the monster casted

// Input: -
// Output: return the attack value of the skill
int Skill::getATK() { return this->ATK; }

// Input: new int attack value
// Output: set the new attack value for the skill
void Skill::setATK(int newATK) {
    this->ATK = newATK;
}

// Input: -
// Output: return the name of the skill
std::string Skill::getNAME() { return this->NAME; }

// Input: -
// Output: return the type of the skill - Shield or ATK
Type Skill::getType() { return this->type; }

// Input: -
// Output: return the its a magic skill or not
bool Skill::getISMAGIC() { return this->isMagic; }

// Input: accept player and monster pointers, and string for the monster action description
// Output: monster damaging the player or creating a shield
// and print out the action and update monster shield HP/ player HP
void Skill::act(Player *player, Monster *monster, string& monster_action_des) {

    // choose whether its a damage action or shield regen action
    switch (this->getType()) {
        case Type::DAMAGE: { // directly damage the player
            int player_hp = player->getHP();
            int monster_attack = this->getATK();
            player->setHP(player_hp - monster_attack);
        }
            break;
        case Type::SHIELD: { // monster will regenerate the shield HP
            monster->setSHIELDHP(monster->getSHIELDHP() + this->getATK());
            monster->setSHIELD_ISMAGIC(this->getISMAGIC());
        }
            break;
    }
}

// Input: Monster Skills Nodes
// Output: load the xml file storing the stats of every monster
void Skill::loadMonsterSkillXML(xml_document& doc) {
    // xml_document doc;

    // load the xml first
    xml_parse_result result = doc.load_file(MONSTER_SKILLS_FILE);

    // quick check whether we load the file successfully or not
    // if (result) {
    //     std::cout << "XML [" << MONSTER_SKILLS_FILE << "] parsed without errors" << endl;
    // }
    // else {
    //     std::cout << "XML [" << MONSTER_SKILLS_FILE << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
    //     std::cout << "Error description: " << result.description() << "\n";
    //     std::cout << "Error offset: " << result.offset << " (error at [..." << (MONSTER_SKILLS_FILE + result.offset) << "]\n\n";
    // }

}
