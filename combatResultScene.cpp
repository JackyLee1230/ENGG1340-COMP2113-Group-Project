#include <iostream>
#include <stdlib.h>
#include <time.h>

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
    // we don't want the player's level reduces
    std::vector<Weapon> weapons = player->getWeapons();

    if(isPlayerWon){
        cout << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=Monster Drop+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" <<endl;

        if (player->getLEVEL() == monster->getID()) {
            player->setLEVEL(monster->getID() + 1);
            Weapon drop = Weapon(monster->getWEAPONDROP());
            weapons.push_back(drop);
            player->setWeapons(weapons);
            player->setHP_MAX(player->getHP_MAX() + 10);
            cout << "You have collected a weapon " << drop.getNAME() << " from the monster" << endl;
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


        SaveLoad::createNewSaveFile(player);
        cout << "You have received " << fruit_quantity << " "<< fruits[fruits.size()-1].getNAME()<< "(s)" << endl;
        cout << "=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=Monster Drop+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+" <<endl;

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
