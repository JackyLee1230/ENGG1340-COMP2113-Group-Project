#include <iostream>
#include <string>
#include <cctype>

// exit
#include <stdlib.h>

// system
#include <cstdlib>

#include "player.h"

#include "saveLoad.h"

#include "sceneManager.h"
#include "titleScene.h"
#include "castleScene.h"
#include "settingScene.h"

using namespace std;

void TitleScene::playScene() {
    // load the graphics
    SceneManager::loadTitleScreen();

    string input = "";
    cin >> input;

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

            // TODO
            // implement savefile check by using the
            // static bool checkSaveFileExist(filename) in Player class

            Player *player = SaveLoad::loadSaveFile();
            Monster *monster = new Monster(1);

            system("clear");

            // ultimately: load the lobby scene

            SceneManager::loadCombatScreen(player, monster);
            // SceneManager::loadEncouterMonster(2);
            //test.loadAsciiArt("monster_2");

        } break;
        case 2: {
            cout << "You inputted: " << user_input << "\n";
            user_input = 0;
            cout << "New Game Started!!!!" << endl;

            CastleScene::playScene();
        }
            break;
        case 3:
            cout << "You inputted: " << user_input << "\n";
            system("clear");
            cout << "Now Accessing SETTINGS";
            //SettingScene::playScene();
            break;
        case 4:
            system("clear");
            cout<< "See you next time! We hope you enjoyed your stay!"<<endl;
            exit(0);
            break;
    }

}
