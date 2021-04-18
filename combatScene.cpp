#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

// nanoseconds()
#include <chrono>
// sleep_for()
#include <thread>

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
    oss << "You have encountered " << monster->getNAME() << "\n" << "Fight For Your Survival!!!!" << "\n" ;

    player_action_des = oss.str();

    oss.str("");
    oss.clear();
    oss << "The Monster has spotted you! " << "\n" << "Beware of their attacks!" << "\n" ;
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
            monster->setHP(0);
            player_action_des = "You earn the victory.\n";
            monster_action_des = "The monster is dead.\n";

            SceneManager::loadCombatScreen(
                player, monster,
                player_action_des,
                monster_action_des
            );

            // decent sleep function
            // to allow player look the final status of the combat
            this_thread::sleep_for(chrono::seconds(2));

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
            player->setHP(0);
            player_action_des = "You lose the battle.\n";
            monster_action_des = "The monster survived.\n";

            SceneManager::loadCombatScreen(
                player, monster,
                player_action_des,
                monster_action_des
            );

            // decent sleep function
            // to allow player look the final status of the combat
            this_thread::sleep_for(chrono::seconds(2));

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

    while(monster->getSHIELDHP() != 0 && skill.getType()== Type::SHIELD && monster->getSHIELD_ISMAGIC() != skill.getISMAGIC() ){
        monster_move =  rand() % (monster->getSkills().size());
        skill = monster->getSkills()[monster_move];
    }

    // clear existing stuff in the ostringstream
    oss.str("");
    oss.clear();

    skill.act(player, monster, monster_action_des);

    if (skill.getType() == Type::DAMAGE) {
        oss << monster->getNAME()
            <<  " casted: " << skill.getNAME()
            << " and dealt " << skill.getATK() << " damage" << "\n";
    }
    else if (skill.getType() == Type::SHIELD) {
        oss << monster->getNAME()
            <<  " casted: " << skill.getNAME()
            << " and built itself a shield!!" << "\n";
    }

    // generate flight movement
    // only for monsters who have FLIGHT variable
    if (monster->getFLIGHT()) {
        switch(monster->fly()) {
            case 1:
                oss << monster->getNAME()
                    << " leaves the ground !!" << "\n";
                break;
            case -1:
                oss << monster->getNAME()
                    << " lands on the ground !!" << "\n";
                break;
            case 0:
                if (monster->getIsFlying()) {
                    oss << monster->getNAME()
                    << " is flying !!" << "\n";
                }
                break;
        }
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
    std::vector<Fruit> fruits = player->getFruits();

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

        // user_input determine which weapon player uses to attack the monster
        switch (user_input) {
            //-------------------------weapons------------------------------
            case 1: {
                //oss << "Using " << weap(ons[0].getNAME() <<" to attack and dealt " << weapons[0].getATK() << " damage to " << monster->getNAME() << "!" ;

                // handling )user inputing a weapon slot which does not exist
                if (weapons.size() < user_input) {
                    cout << "Input invalid. Please try again." << endl;
                }
                else {
                    weapons[0].attack(monster, player_action_des);
                    continue_game = true;
                }
                }
                break;
            case 2: {
                //oss << "Using " << weapons[1].getNAME() <<" to attack and dealt " << weapons[1].getATK() << " damage to " << monster->getNAME() << "!" ;

                // handling user inputing a weapon slot which does not exist
                if (weapons.size() < user_input) {
                    cout << "Input invalid. Please try again." << endl;
                }
                else {
                    weapons[1].attack(monster, player_action_des);
                    continue_game = true;
                }
                }
                break;
            case 3:{
                //oss << "Using " << weapons[2].getNAME() <<" to attack and dealt " << weapons[2].getATK() << " damage to " << monster->getNAME() << "!" ;

                // handling user inputing a weapon slot which does not exist
                if (weapons.size() < user_input) {
                    cout << "Input invalid. Please try again." << endl;
                }
                else {
                    weapons[2].attack(monster, player_action_des);
                    continue_game = true;
                }
                }
                break;
            case 4:{
                //oss << "Using " << weapons[3].getNAME() <<" to attack and dealt " << weapons[3].getATK() << " damage to " << monster->getNAME() << "!" ;

                // handling user inputing a weapon slot which does not exist
                if (weapons.size() < user_input) {
                    cout << "Input invalid. Please try again." << endl;
                }
                else {
                    weapons[3].attack(monster, player_action_des);
                    continue_game = true;
                }
                }
                break;
            // --------------- consumables(fruits) --------------
            case 5:{
                // handling user inputing a fruit slot which does not exist
                if (fruits.size() + 4 < user_input) {
                    cout << "Input invalid. Please try again." << endl;
                }
                else {
                    int fruit_status = fruits[0].act(player);

                    // if consumed the last fruit
                    // -> quantity of the fruit = 0
                    if (fruit_status) {
                        // remove that fruit from the player's fruits list
                        fruits.erase(fruits.begin() + 0);
                    }

                    // update the fruit vectors in the player object
                    player->setFruits(fruits);

                    continue_game = false;
                    player_action_des = "You consumed " + fruits[0].getNAME() + " and healed " + to_string(fruits[0].getHP()) + " HP!";

                    // display whether the monster is flying or not
                    // to give info to player to decide to use which weapon
                    if (monster->getFLIGHT()) {
                        monster_action_des = monster->getFlightDescription();
                    }
                    else {
                        monster_action_des = "";
                    }

                    SceneManager::loadCombatScreen(player, monster, player_action_des, monster_action_des);
                    // reset description
                    player_action_des = "";
                }
            }
            break;
            case 6:{
                // handling user inputing a fruit slot which does not exist
                if (fruits.size() + 4 < user_input) {
                    cout << "Input invalid. Please try again." << endl;
                }
                else {
                    int fruit_status = fruits[1].act(player);

                    // if consumed the last fruit
                    // -> quantity of the fruit = 0
                    if (fruit_status) {
                        fruits.erase(fruits.begin() + 1);
                    }

                    // update the fruit vectors in the player object
                    player->setFruits(fruits);

                    continue_game = false;
                    player_action_des = "You consumed " + fruits[1].getNAME() + " and healed " + to_string(fruits[1].getHP()) + " HP!";

                    if (monster->getFLIGHT()) {
                        monster_action_des = monster->getFlightDescription();
                    }
                    else {
                        monster_action_des = "";
                    }

                    SceneManager::loadCombatScreen(player, monster, player_action_des, monster_action_des);

                    // reset description
                    player_action_des = "";
                }
            }
            break;
            case 7:{
                // handling user inputing a fruit slot which does not exist
                if (fruits.size() + 4 < user_input) {
                    cout << "Input invalid. Please try again." << endl;
                }
                else {
                    int fruit_status = fruits[2].act(player);

                    // if consumed the last fruit
                    // -> quantity of the fruit = 0
                    if (fruit_status) {
                        fruits.erase(fruits.begin() + 2);
                    }

                    // update the fruit vectors in the player object
                    player->setFruits(fruits);

                    continue_game = false;
                    player_action_des = "You consumed " + fruits[2].getNAME() + " and healed " + to_string(fruits[2].getHP()) + " HP!";

                    if (monster->getFLIGHT()) {
                        monster_action_des = monster->getFlightDescription();
                    }
                    else {
                        monster_action_des = "";
                    }

                    SceneManager::loadCombatScreen(player, monster, player_action_des, monster_action_des);

                    // reset description
                    player_action_des = "";
                }
            }
            break;
            case 8:{
                // handling user inputing a fruit slot which does not exist
                if (fruits.size() + 4 < user_input) {
                    cout << "Input invalid. Please try again." << endl;
                }
                else {
                    int fruit_status = fruits[3].act(player);

                    // if consumed the last fruit
                    // -> quantity of the fruit = 0
                    if (fruit_status) {
                        fruits.erase(fruits.begin() + 3);
                    }

                    // update the fruit vectors in the player object
                    player->setFruits(fruits);

                    continue_game = false;
                    player_action_des = "You consumed " + fruits[3].getNAME() + " and healed " + to_string(fruits[3].getHP()) + " HP!";

                    if (monster->getFLIGHT()) {
                        monster_action_des = monster->getFlightDescription();
                    }
                    else {
                        monster_action_des = "";
                    }

                    SceneManager::loadCombatScreen(player, monster, player_action_des, monster_action_des);

                    // reset description
                    player_action_des = "";
                }
            }
            break;
            case 9:{
                // handling user inputing a fruit slot which does not exist
                if (fruits.size() + 4 < user_input) {
                    cout << "Input invalid. Please try again." << endl;
                }
                else {
                    int fruit_status = fruits[4].act(player);

                    // if consumed the last fruit
                    // -> quantity of the fruit = 0
                    if (fruit_status) {
                        fruits.erase(fruits.begin() + 4);
                    }

                    // update the fruit vectors in the player object
                    player->setFruits(fruits);

                    continue_game = false;
                    player_action_des = "You consumed " + fruits[4].getNAME() + " and healed " + to_string(fruits[4].getHP()) + " HP!";

                    if (monster->getFLIGHT()) {
                        monster_action_des = monster->getFlightDescription();
                    }
                    else {
                        monster_action_des = "";
                    }

                    SceneManager::loadCombatScreen(player, monster, player_action_des, monster_action_des);

                    // reset description
                    player_action_des = "";
                }
            }
            break;
            case 10:{
                // handling user inputing a fruit slot which does not exist
                if (fruits.size() + 4 < user_input) {
                    cout << "Input invalid. Please try again." << endl;
                }
                else {
                    int fruit_status = fruits[5].act(player);

                    // if consumed the last fruit
                    // -> quantity of the fruit = 0
                    if (fruit_status) {
                        fruits.erase(fruits.begin() + 5);
                    }

                    // update the fruit vectors in the player object
                    player->setFruits(fruits);

                    continue_game = false;
                    player_action_des = "You consumed " + fruits[5].getNAME() + " and healed " + to_string(fruits[5].getHP()) + " HP!";

                    if (monster->getFLIGHT()) {
                        monster_action_des = monster->getFlightDescription();
                    }
                    else {
                        monster_action_des = "";
                    }

                    SceneManager::loadCombatScreen(player, monster, player_action_des, monster_action_des);

                    // reset description
                    player_action_des = "";
                }
            }
            break;
        }
    }

    // store the action description for displaying
    // clear it after each turn to prevent message stacking
    oss.clear();

}
