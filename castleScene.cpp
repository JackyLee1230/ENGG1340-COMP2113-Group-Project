#include <iostream>
#include <string>

// isdigit()
#include <cctype>

#include "castleScene.h"

#include "sceneManager.h"
#include "combatScene.h"
// #include "lobbyScene.h"
#include "saveLoad.h"
#include "player.h"

using namespace std;

void CastleScene::playScene() {

    // load scene
    SceneManager::loadCastleScreen();

    cout << "Enter 1 if you have read through the background story"<< endl;
    cout << "and want to start the game!" << endl;

    string input = "";
    getline(cin, input);

    // input check
    while(input.length() !=1 || isdigit(input[0]) == 0 || std::stoi(input) != 1){
        cout << "Enter 1 if you have read through the background story"<< endl;
        cout << "and want to start the game!" << endl;
        getline(cin, input);
     }

     // create a new player object with default value and weapons
     // written in the constructor
     Player *player = new Player(30, 1, 0, 0);

     // create our first monster
     Monster *monster = new Monster(1);
     // create a new save file with default player value
     SaveLoad::createNewSaveFile(player);

     // final goal: load the combat scene to first for the first monster
     CombatScene::playScene(player, monster);

}
