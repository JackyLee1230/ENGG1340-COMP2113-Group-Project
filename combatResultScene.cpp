#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>

#include "combatResultScene.h"

#include "sceneManager.h"
#include "lobbyScene.h"
#include "combatScene.h"
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

        // give player fruits after each win
        std::vector<Fruit> fruits = player->getFruits();
        srand(unsigned(time(NULL))); // random prob using time
        int fruit_type = (int) 1 + ( rand() % 5 );
        srand(unsigned(time(NULL))); // random prob using time
        int fruit_quantity = (int) 1 + ( rand() % 10 );

        bool added = false;

        for(int i = 0; i< fruits.size(); i++){
            if(fruits[i].getID() == fruit_type){
                fruits[i].setQUANTITY(fruits[fruit_type].getQUANTITY() + fruit_quantity);
                added = true;
            }
        }
        if(added == false){
            fruits.push_back(Fruit(fruit_type, fruit_quantity));
            //fruits[fruits.size()-1].setQUANTITY(fruit_quantity);
        }

        player->setFruits(fruits);

        cout << "You have received " << fruit_quantity << " "<< fruits[fruits.size()-1].getNAME()<< "(s)" << endl;
        cout << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=Monster Drop+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" <<endl;

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
        // release memory of the monster
        // allow the next monster to be created later
        delete monster;

        //quit the game once the player has defeated the final BOSS
        // and display the final end game scene
        if (player->getLEVEL() == 6){
            SceneManager::loadEndGameScreen();
            exit(0);
        }

        // after finishing the current level, go back to the lobby
        // load the lobby scene
        LobbyScene::playScene(player);
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
