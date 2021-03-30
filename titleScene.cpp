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
#include "lobbyScene.h"
#include "settingScene.h"

using namespace std;

void TitleScene::playScene() {
    // load the graphics
    SceneManager::loadTitleScreen();

    string input = "";
    getline(cin, input);

    // input check
    while(true){
        if ((input.length() !=1) || (isdigit(input[0]) == 0) || (std::stoi(input) <= 0) || (std::stoi(input) >= 5)) {
            cout << "PLEASE ENTER CHOICE BETWEEN 1 - 4" << endl;
        }
        else {
            int user_input = std::stoi(input);

            if (user_input == 1) {
                if (!SaveLoad::checkSaveFileExist())
                    cout << "Savefile does not exist. Please enter 2 to start a new game instead." << endl;
                else
                    break;
            }
            else
                break;
        }

        getline(cin, input);
        // cout << user_input << "\n";
     }

    int user_input = std::stoi(input);

    switch (user_input) {
        case 1: {
            cout << "You inputted: " << user_input << "\n";

            system("clear");

            Player *player = SaveLoad::loadSaveFile();

            // load the lobby scene
            LobbyScene::playScene(player);

        } break;
        case 2: {
            cout << "You inputted: " << user_input << "\n";
            cout << "New Game Started!!!!" << endl;

            system("clear");

            CastleScene::playScene();
        } break;
        case 3: {

            // use for testing new features (like combat scenes)
            cout << "You inputted: " << user_input << "\n";

            Player *player = SaveLoad::loadSaveFile();
            Monster *monster = new Monster(1);

            system("clear");
            // cout << "Now Accessing SETTINGS";
            //SettingScene::playScene();

            SceneManager::loadCombatScreen(player, monster);
        } break;
        case 4:
            system("clear");
            cout<< "See you next time! We hope you enjoyed your stay!"<<endl;
            exit(0);
            break;
    }

}
