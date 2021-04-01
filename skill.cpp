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

int Skill::getATK() { return ATK; }

void Skill::setATK(int newATK) {
    ATK = newATK;
}

std::string Skill::getNAME() { return NAME; }

// monster damaging the player
void Skill::act(Player *player, Monster *monster, Skill *skill, int dmg_type, string& monster_action_des){

    switch(dmg_type){

        // pure physical damage
        case 1: {
            int player_hp = player->getHP();
            int monster_attack = skill->getATK();
            player->setHP(player_hp - monster_attack);

        } break;
        // case 2: // damage to shield
            // Type type;
            // int player = monster.getATK();
            // if(monster_attack > ShieldHP){
            // }
            // break;
    }
}

// player attacking the monster
// void Skill::attack(Player *player, Monster *monster, int damage){
//     srand(unsigned(time(NULL)));
//     double dodge_prob = monster->getDODGE() / 100;// probability of dodge depend on the monster
//     double roll = (double) (rand() / (RAND_MAX + 1.0)); //generate rand prob with time
//     if(roll > dodge_prob){
//         if(monster->getHP() > damage){
//             // reduce HP by dmg value
//             monster->setHP(monster->getHP() - damage);
//         }else if(monster->getHP() == damage){
//             monster->setHP(0);
//             cout << "You barely defeated the Monster and it fainted." << endl;
//         }else if(damage > monster->getHP()){
//             // set HP to 0 since player damage is higher than monster health
//             monster->setHP(0);
//         }
//     }else{
//         cout << "The Monster were quick enough to realised and evaded your attack!!!!" << endl;
//         monster->setHP(monster->getHP());
//     }
// }



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
