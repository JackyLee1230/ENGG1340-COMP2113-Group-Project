#include <iostream>
#include <string>
#include <cctype>

// exit
#include <stdlib.h>

// file.open() .close()
#include <fstream>

// system
#include <cstdlib>

#include "sceneManager.h"
#include "titleScene.h"
#include "monster.h"
#include "player.h"
#include "settingScene.h"
#include "saveLoad.h"
#include "lobbyScene.h"

#include "pugixml/pugixml.hpp"

using namespace std;
using namespace pugi;

void LobbyScene::playScene(Player *player) {

    int current_floor = player->getFLOOR();

    // load the graphics
    SceneManager::loadLobbyFloor(current_floor);
    SceneManager::loadLobbyScreen();

    // test player object
    cout << "Player's HP = " <<  player->getHP() << "; DODGE = " << player->getDODGE() << "; FLOOR = " << player->getFLOOR() << endl;

    string input = "";
    getline(cin, input);

    // input check
    while(input.length() !=1 || isdigit(input[0]) == 0 || std::stoi(input) <= 0 || std::stoi(input) >= 7){
        cout << "PLEASE ENTER CHOICE BETWEEN 1 - 6" << endl;
        getline(cin, input);
     }

    int user_input = std::stoi(input);
    switch (user_input) {
        case 1: {
            system("clear");
            cout << "Accessing Armory!" << "\n";
            cout << "Gear up for your next battle!";
            }
            break;
        case 2: {
            system("clear");
            cout << "Accessing Food Storage Room";
            }
            break;
        case 3:
            system("clear");
            cout << "Now Accessing Rest Room";
            break;
        case 4:
            system("clear");
            cout << "Now Accessing the LEVEL BOSS!!!" << "\n";
            cout << "Prepare for CHAOS!";
            // Load Combat Scene
            break;
        case 5:
        // SAVE GAME
            system("clear");
            cout << "SAVING GAME";
            if(!SaveLoad::checkSaveFileExist()){
                // SaveLoad::createNewSaveFile(30, 1, "test");
            }
            //SettingScene::playScene();
            break;
        case 6:
            system("clear");
            cout<< "See you next time! We hope you enjoyed your stay!"<<endl;
            exit(0);
            break;
    }

}
