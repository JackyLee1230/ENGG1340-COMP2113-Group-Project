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
        player->setLEVEL(player->getLEVEL() + 1);
        SaveLoad::createNewSaveFile(player);

        // release memory of the monster
        delete monster;

        // load the lobby scene
        LobbyScene::playScene(player);
    }
    else {

        if (user_input == "R") {
            // create a new monster with the same id of the previous one
            Monster *newMonster = new Monster(monster->getID());

            // remove the original one
            delete monster;

            // refill the HP of the player
            player->setHP(Player::HP_MAX);

            // load the combat scene again
            CombatScene::playScene(player, newMonster);
        }
        else if (user_input == "Q") {
            delete monster;

            // refill the HP of the player
            player->setHP(Player::HP_MAX);

            // load the lobby scene
            LobbyScene::playScene(player);
        }
    }
}
