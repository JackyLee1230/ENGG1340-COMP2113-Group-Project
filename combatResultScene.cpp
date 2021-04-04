#include <iostream>

#include "combatResultScene.h"

#include "sceneManager.h"
#include "lobbyScene.h"
#include "combatScene.h"
#include "saveLoad.h"

using namespace std;

void CombatResultScene::playScene(Player *player, Monster *monster, bool isPlayerWon) {

    // load graphics
    SceneManager::loadCombatResultScreen(isPlayerWon);

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
        // handle savefile stuff

        // we don't want the player's level reduces
        if (player->getLEVEL() == monster->getID()) {
            player->setLEVEL(monster->getID() + 1);
        }

        SaveLoad::createNewSaveFile(player);

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
            player->setHP(Player::HP_MAX);

            // load the combat scene again
            CombatScene::playScene(player, newMonster);
        }
        else if (user_input == "Q") { // Quit and go back to the lobby
            // remove the original one
            // allow the monster to be recreated
            delete monster;

            // refill the HP of the player
            player->setHP(Player::HP_MAX);

            // load the lobby scene
            LobbyScene::playScene(player);
        }
    }
}
