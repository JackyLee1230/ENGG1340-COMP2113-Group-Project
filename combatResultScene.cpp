#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <vector>

// for shuffle()
#include <algorithm>

#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

#include "combatResultScene.h"

#include "sceneManager.h"
#include "lobbyScene.h"
#include "combatScene.h"
#include "storyScene.h"
#include "saveLoad.h"

using namespace std;

void CombatResultScene::playScene(Player *player, Monster *monster, bool isPlayerWon) {

    // load graphics
    SceneManager::loadCombatResultScreen(isPlayerWon);

    // --------------------item and fruit drop ---------------------
    std::vector<Weapon> weapons = player->getWeapons();

    if(isPlayerWon){
        cout << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=Monster Drop+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" <<endl;

        // defeated the monster for the first time
        if (player->getLEVEL() + 1 == monster->getID()) {
            player->setLEVEL(monster->getID());

            if(monster->getWEAPONDROP() != -1){
                Weapon drop = Weapon(monster->getWEAPONDROP());
                cout << "You have collected a weapon " << drop.getNAME() << " from the monster" << endl;

                // show the stats of the new weapon to give complete information to the player
                // preserve some spacing
                cout << "    ";
                drop.showWeapon();
                cout << endl;

                // ask the player to drop a weapon if owning four weapons already
                if (weapons.size() == 4) {
                    string input = "";

                    cout << "Please input 1-4 to replace the weapon with the new one" << endl;

                    // display all weapons
                    for (int i = 0; i < weapons.size(); i++) {
                        cout << "[" << (i+1) << "] "; // show hint for user input
                        weapons[i].showWeapon();
                        cout << endl;
                    }

                    getline(cin, input);
                    // prompt for player input until input is valid
                    while(isdigit(input[0]) == 0 || std::stoi(input) <= 0 || std::stoi(input) >= 5){
                        cout << "PLEASE ENTER CHOICE BETWEEN 1 - 4" << endl;
                        getline(cin, input);
                     }

                    int user_input = std::stoi(input);


                    cout << "You choose to drop " << weapons[user_input - 1].getNAME() << endl;
                    weapons[user_input - 1] = drop;
                }
                else {
                    weapons.push_back(drop);
                }
            }

            player->setWeapons(weapons);
            player->updateNewHP_MAX();
        }

        // -------------------------Fruit Drop-------------------------
        // give player fruits after each win
        std::vector<Fruit> fruits = player->getFruits();

        // generate random dropping multiple fruits with non-replace fruit types
        srand(unsigned(time(NULL)));
        // minimum: 1, maximum: 3
        int num_of_fruit_types = (int)(rand() % 3) + 1;

        std::vector<int> fruit_ids;
        for (int i = 0; i < 5; i++) {
            fruit_ids.push_back(i + 1);
        }

        // obtain a time-based seed
        unsigned seed = unsigned(time(NULL));
        shuffle(fruit_ids.begin(), fruit_ids.end(), std::default_random_engine(seed));

        srand(unsigned(time(NULL))); // random prob using time

        // for each fruit type...
        for (int i = 0; i < num_of_fruit_types; i++) {
            int fruit_quantity;

            // changing the upper and lower bound of number of fruits dropped
            // for different types of fruits
            switch(static_cast<FruitID>(fruit_ids[i])) {
                case DRAGONS_FRUIT:
                    // lower bound: 5, upper bound: 15
                    fruit_quantity = (int)(rand() % 10) + 5;
                    break;

                case PEACH:
                    // lower bound: 1, upper bound: 5
                    fruit_quantity = (int)(rand() % 5) + 1;
                    break;

                default:
                    // lower bound: 15, upper bound: 30
                    fruit_quantity = (int)(rand() % 15) + 15;


            }

            bool added = false;

            // check whether that type of fruit exists or not in the player's inventory
            for(int j = 0; j < fruits.size(); j++){
                if(fruits[j].getID() == fruit_ids[i]){
                    fruits[j].setQUANTITY(fruits[j].getQUANTITY() + fruit_quantity);
                    added = true;

                    // output to the screen
                    cout << "You have received " << fruit_quantity << " " << fruits[j].getNAME() << "(s)" << endl;

                    break;
                }
            }

            if(!added){
                fruits.push_back(
                    Fruit(fruit_ids[i], fruit_quantity)
                );

                // output to the screen
                cout << "You have received " << fruit_quantity << " " << fruits[fruits.size() - 1].getNAME() << "(s)" << endl;
            }


        }

        cout << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=Monster Drop+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" <<endl;

        player->setFruits(fruits);

        // auto recover HP when winning
        player->setHP(player->getHP_MAX());

        SaveLoad::createNewSaveFile(player);
    }


    string user_input = "";

    getline(cin, user_input);

    // user input check to determine game action
    while (true) {
        if (user_input.length() == 1) {
            if (user_input == "n" && isPlayerWon)
                break;
            else if (!isPlayerWon && (user_input == "R" || user_input == "Q"))
                break;
        }

        getline(cin, user_input);
    }

    if (isPlayerWon) {
        // not the GateKeeper
        if (monster->getID() != 1)
            StoryScene::playScene(player, monster);
        else {
            delete monster;

            LobbyScene::playScene(player);
        }
    }
    else if (!isPlayerWon) {

        if (user_input == "R") { // Retry the monster fight
            // create a new monster with the same id of the previous one
            Monster *newMonster = new Monster(monster->getID());

            // remove the original one
            // allow the monster to be recreated
            delete monster;

            // refill the HP of the player
            player->setHP(player->getHP_MAX());

            // load the combat scene again
            CombatScene::playScene(player, newMonster);
        }
        else if (user_input == "Q") { // Quit and go back to the lobby
            // remove the original one
            // allow the monster to be recreated
            delete monster;

            // refill the HP of the player
            player->setHP(player->getHP_MAX());

            // load the lobby scene
            LobbyScene::playScene(player);
        }
    }
}
