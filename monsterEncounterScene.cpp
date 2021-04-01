#include <iostream>

// getline()
#include <string>

#include "monsterEncounterScene.h"

#include "sceneManager.h"
#include "combatScene.h"

#include "player.h"
#include "monster.h"

using namespace std;

void MonsterEncounterScene::playScene(Player *player, Monster *monster) {

    // load graphics
    SceneManager::loadEncouterMonster(monster->getID());

    cout << "Enter 'n' to continue and fight " + monster->getNAME();

    // input handling
    string input = "";
    getline(cin, input);

    while(true) {
        if (input == "n"){
            break;
        }

        getline(cin, input);
    }


    cout<<"You have chosen to fight " + monster->getNAME() + "! Prepare yourself!";
    CombatScene::playScene(player, monster);
}
