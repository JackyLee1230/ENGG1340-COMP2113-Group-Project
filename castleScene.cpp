#include <iostream>
#include <string>

// isdigit()
#include <cctype>

#include "castleScene.h"

#include "sceneManager.h"
#include "lobbyScene.h"
#include "saveLoad.h"
#include "player.h"

using namespace std;

void CastleScene::playScene() {

    // load scene
    SceneManager::loadCastleScreen();

    cout << "Enter 1 if you have read through the background story"<< endl;
    cout << "and want to start the game!" << endl;

    string input = "";
    cin >> input;

    // input check
    while(input.length() !=1 || isdigit(input[0]) == 0 || std::stoi(input) != 1){
        cout << "Enter 1 if you have read through the background story"<< endl;
        cout << "and want to start the game!" << endl;
        cin >> input;
     }

     // create a new player object with default value
     // and allocate it to the heap memory
     Player *player = new Player(30, 1, 0);

     // create a new save file with default player value
     SaveLoad::createNewSaveFile(player);

     // final goal: load the combat scene to first for the first monster

     // right now load the lobby scene to test for their functionability
     // pass our player object in heap
     LobbyScene::playScene(player);

}
