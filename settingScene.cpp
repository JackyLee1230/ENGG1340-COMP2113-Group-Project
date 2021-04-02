#include <iostream>
#include <string>
#include <cctype>

// exit
#include <stdlib.h>

// system
#include <cstdlib>

#include "sceneManager.h"
#include "titleScene.h"
#include "monster.h"
#include "settingScene.h"
#include "player.h"
#include "weapon.h"

using namespace std;

//load the setting scene 
void SettingScene::playScene() {
    SceneManager::loadSettingScreen();

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
            cout << "You inputted: " << user_input << "\n";
        } break;
        case 2:
            cout << "You inputted: " << user_input << "\n";
            break;
        case 3:
            cout << "You inputted: " << user_input << "\n";
            system("clear");
            break;
        case 4:
            exit(0);
            break;
    }

}
