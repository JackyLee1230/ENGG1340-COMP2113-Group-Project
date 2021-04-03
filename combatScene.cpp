#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

#include "combatScene.h"

#include "saveLoad.h"
#include "player.h"
#include "monster.h"
#include "skill.h"

#include "SceneManager.h"
#include "titleScene.h"
#include "settingScene.h"
#include "lobbyScene.h"
#include "combatResultScene.h"
#include "fruit.h"

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

    bool isPlayerWon = false;

    // generate our first-encounter string here
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

            // load the combat screen with the hp of the monster is set to 0
            // wait for a few seconds


            // load the corresponding scene
            CombatResultScene::playScene(player, monster, true);
            break;
        }
        // turn based, next- monster go next
        monsterMove(player, monster);


        if (player->getHP() <= 0) {
            // monster wins, player loses

            // load the combat screen with the hp of the player is set to 0
            // wait for a few seconds


            // load the corresponding scene
            CombatResultScene::playScene(player, monster, false);
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

// randomly generate a monster move
// and output the monster's move and deal the corresponding damage to the player
void monsterMove(Player *player, Monster *monster) {
    // Randomly choose monster's move
    int monster_move =  rand() % (monster->getSkills().size());
    Skill skill = monster->getSkills()[monster_move];

    // clear existing stuff in the ostringstream
    oss.str("");
    oss.clear();

    skill.act(player, monster, monster_action_des);

    if (skill.getType() == Type::DAMAGE) {
        oss << monster->getNAME()
            <<  " casted: " << skill.getNAME()
            << " and dealt " << skill.getATK() << " damage";
    }
    else if (skill.getType() == Type::SHIELD) {
        oss << monster->getNAME()
            <<  " casted: " << skill.getNAME()
            << " and built itself a shield!!" ;
    }


    // store the action description for displaying
    monster_action_des = oss.str();
}


// ask for player weapon use
// and output the plater's weapon choice and deal the corresponding damage to the monster
void playerMove(Player *player, Monster *monster) {
    player_action_des = "";
    //ask for player input for action
    string input = "";

    // save all of the player weapons into a vector
    std::vector<Weapon> weapons = player->getWeapons();
    SaveLoad::loadSaveFile();
    std::vector<Fruit> fruits = player->getFRUITS();


    bool continue_game = false;

    while(continue_game == false){

        getline(cin, input);
        // prompt for player input until input is valid
        while(isdigit(input[0]) == 0 || std::stoi(input) <= 0 || std::stoi(input) >= 10){
            cout << "PLEASE ENTER CHOICE BETWEEN 1 - 4 For Attack, 5-10 For Healing" << endl;
            getline(cin, input);
         }

        int user_input = std::stoi(input);

        // clear existing stuff in the ostringstream
        oss.str("");
        oss.clear();

        cout << endl;

        // user_input determine which weapon player uses to attack the monster
        switch (user_input) {
            case 1: {
                //oss << "Using " << weapons[0].getNAME() <<" to attack and dealt " << weapons[0].getATK() << " damage to " << monster->getNAME() << "!" ;
                weapons[0].attack(monster, player_action_des);
                continue_game = true;
                }
                break;
            case 2: {
                //oss << "Using " << weapons[1].getNAME() <<" to attack and dealt " << weapons[1].getATK() << " damage to " << monster->getNAME() << "!" ;
                weapons[1].attack(monster, player_action_des);
                continue_game = true;
                }
                break;
            case 3:{
                //oss << "Using " << weapons[2].getNAME() <<" to attack and dealt " << weapons[2].getATK() << " damage to " << monster->getNAME() << "!" ;
                weapons[2].attack(monster, player_action_des);
                continue_game = true;
                }
                break;
            case 4:{
                //oss << "Using " << weapons[3].getNAME() <<" to attack and dealt " << weapons[3].getATK() << " damage to " << monster->getNAME() << "!" ;
                weapons[3].attack(monster, player_action_des);
                continue_game = true;
                }
            // --------------- consumables --------------
            case 5:{
                fruits[0].act(player);
                continue_game = false;
                player_action_des = "You consumed " + fruits[0].getNAME() + " and healed " + to_string(fruits[0].getHP()) + " HP!";
                monster_action_des ="";
                SceneManager::loadCombatScreen(player, monster, player_action_des, monster_action_des);
            }
            break;
            case 6:{
                fruits[1].act(player);
                continue_game = false;
                player_action_des = "You consumed " + fruits[1].getNAME() + " and healed " + to_string(fruits[1].getHP()) + " HP!";
                monster_action_des ="";
                SceneManager::loadCombatScreen(player, monster, player_action_des, monster_action_des);
            }
            break;
            case 7:{
                fruits[2].act(player);
                continue_game = false;
                player_action_des = "You consumed " + fruits[2].getNAME() + " and healed " + to_string(fruits[2].getHP()) + " HP!";
                monster_action_des ="";
                SceneManager::loadCombatScreen(player, monster, player_action_des, monster_action_des);
            }
            break;
            case 8:{
                fruits[3].act(player);
                continue_game = false;
                player_action_des = "You consumed " + fruits[3].getNAME() + " and healed " + to_string(fruits[3].getHP()) + " HP!";
                monster_action_des ="";
                SceneManager::loadCombatScreen(player, monster, player_action_des, monster_action_des);
            }
            break;
            case 9:{
                fruits[4].act(player);
                continue_game = false;
                player_action_des = "You consumed " + fruits[4].getNAME() + " and healed " + to_string(fruits[4].getHP()) + " HP!";
                monster_action_des ="";
                SceneManager::loadCombatScreen(player, monster, player_action_des, monster_action_des);
            }
            break;
            case 10:{
                fruits[5].act(player);
                continue_game = false;
                player_action_des = "You consumed " + fruits[5].getNAME() + " and healed " + to_string(fruits[5].getHP()) + " HP!";
                monster_action_des ="";
                SceneManager::loadCombatScreen(player, monster, player_action_des, monster_action_des);
            }
            break;
        }
    }

    // store the action description for displaying
    oss.clear();

}
