#include "combatScene.h"
#include "monster.h"
#include "skill.h"
#include "lobbyScene.h"
#include "SceneManager.h"
#include "player.h"
#include "titleScene.h"
#include "settingScene.h"
#include "saveLoad.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

// for producing formatted string
#include <sstream>      // std::ostringstream

#include "pugixml/pugixml.hpp"

using namespace std;
using namespace pugi;

// place the declaration here as it should not be called from other classes
void playerMove(Player *, Monster *);
void monsterMove(Player *, Monster *);

ostringstream oss;
string player_action_des = "";
string monster_action_des = "";

// should pass the player's and monster's detail
void CombatScene::playScene(Player *player, Monster *monster) {

    // generate our first-encounter string here
    // player_action_des = ;
    // monster_action_des = ;

    oss.str("");
    oss.clear();
    oss << "You have encountered " << monster->getNAME() << "\n" << "Fight for your survival!!!!" ;

    player_action_des = oss.str();

    oss.str("");
    oss.clear();
    oss << "The Monster has spotted you! " << "\n" << "Beware of their attacks!" ;
    monster_action_des = oss.str();

    // load the graphics
    SceneManager::loadCombatScreen(
        player, monster,
        player_action_des,
        monster_action_des
    );

    // our game !!
    while (true) {
        // turn based, first- player go first
        playerMove(player, monster);

        if (monster->getHP() <= 0) {
            // player wins
            // load the corresponding scene
            break;
        }
        // turn based, next- monster go next
        monsterMove(player, monster);


        if (player->getHP() <= 0) {
            // monster wins, player loses
            // load the corresponding scene
            break;
        }

        // update the graphics (some HP and wordings displayed)
        SceneManager::loadCombatScreen(
            player, monster,
            player_action_des,
            monster_action_des
        );
    }
}

void monsterMove(Player *player, Monster *monster) {
    // Randomly choose monster's move
    int monster_move =  rand() % (monster->getSKILLHIGH() - monster->getSKILLLOW() + 1) + monster->getSKILLLOW();
    Skill *skill = new Skill(monster_move);

    // clear existing stuff in the ostringstream
    oss.str("");
    oss.clear();

    skill->act(player, monster, skill , 1, monster_action_des);

    oss << "Monster " << monster->getNAME() <<  " casted: " << skill->getNAME() << " and dealt " << skill->getATK() << " damage";
    // cout << "End of Monster's Turn!" << endl;
    // cout << "Time for you to fight back! Warrior!" << endl;

    // store the action description for displaying
    monster_action_des = oss.str();
}

void playerMove(Player *player, Monster *monster) {
    player_action_des = "";
    //ask for player input for action
    string input = "";
    getline(cin, input);

    std::vector<Weapon> weapons = player->getWeapons();

    while(input.length() !=1 || isdigit(input[0]) == 0 || std::stoi(input) <= 0 || std::stoi(input) >= 4 || std::stoi(input) > weapons.size()){
        cout << "PLEASE ENTER CHOICE BETWEEN 1 - 4" << endl;
        getline(cin, input);
     }

    int user_input = std::stoi(input);

    // clear existing stuff in the ostringstream
    oss.str("");
    oss.clear();

    cout << endl;

    switch (user_input) {
        case 1: {
            //oss << "Using " << weapons[0].getNAME() <<" to attack and dealt " << weapons[0].getATK() << " damage to " << monster->getNAME() << "!" ;
            weapons[0].attack(monster, player_action_des);
            }
            break;
        case 2: {
            //oss << "Using " << weapons[1].getNAME() <<" to attack and dealt " << weapons[1].getATK() << " damage to " << monster->getNAME() << "!" ;
            weapons[1].attack(monster, player_action_des);
            }
            break;
        case 3:{
            //oss << "Using " << weapons[2].getNAME() <<" to attack and dealt " << weapons[2].getATK() << " damage to " << monster->getNAME() << "!" ;
            weapons[2].attack(monster, player_action_des);
            }
            break;
        case 4:{
            //oss << "Using " << weapons[3].getNAME() <<" to attack and dealt " << weapons[3].getATK() << " damage to " << monster->getNAME() << "!" ;
            weapons[3].attack(monster, player_action_des);
            }
            break;
    }

    // store the action description for displaying
    oss.clear();

}
