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

void LobbyScene::playScene() {
    // load the graphics
    //SceneManager::loadLobbyScreen();
    int floor_no = Player::getFLOOR();
    string input = "";
    cin >> input;

    // TODO
    // input check
    while(input.length() !=1 || isdigit(input[0]) == 0 || std::stoi(input) <= 0 || std::stoi(input) >= 5){
        cout << "PLEASE ENTER CHOICE BETWEEN 1 - 4" << endl;
        cin >> input;
        // cout << user_input << "\n";
     }

    int user_input = std::stoi(input);
    switch (user_input) {
        case 1: {
            cout << "You have chosen to enter the next room!" << user_input << "\n";
            system("clear");
        }
        break;

        case 2: {
            // save game
            system("clear");
            cout << "You inputted: " << user_input << "\n";
            }
            break;
        case 3:
            system("clear");
            cout << "Now Accessing Inventory";
            //SettingScene::playScene();
            break;
        case 4:
            system("clear");
            cout<< "See you next time! We hope you enjoyed your stay!"<<endl;
            exit(0);
            break;
    }

}
