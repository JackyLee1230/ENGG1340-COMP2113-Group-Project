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
#include "player.h"
#include "settingScene.h"

using namespace std;

void TitleScene::playScene() {
    // load the graphics
    SceneManager::loadTitleScreen();

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

            // TODO
            // implement savefile check by using the
            // static bool checkSaveFileExist(filename) in Player class

            system("clear");
            SceneManager::loadCombatScreen();
            // SceneManager::loadEncouterMonster(2);
            //test.loadAsciiArt("monster_2");

        } break;
        case 2: {
            cout << "You inputted: " << user_input << "\n";
            user_input = 0;
            cout << "New Game Started!!!!" << endl;
            SceneManager::loadCastleScreen();
            cout << "\n";
            cout << "Enter 1 if you have read through the background story"<< endl;
            cout << "and want to start the game!" << endl;

            // TODO
            // need fix
            // not get stuck in while loop after inputting a non-digit char
            while(true){
                cin >> user_input;
                if(user_input == 1){
                    break;
                }
            }

            // create a new player
            Player player = Player(false);
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
