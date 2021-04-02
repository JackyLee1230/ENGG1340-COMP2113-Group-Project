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
#include "combatScene.h"
#include "combatResultScene.h"

using namespace std;

// this function will load the starting scene of the game
// and prompt for user input to determine whether player
// want to start new game, continue, show credit/info or quit
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

            // check whether a savefile exists before allowing the player to continue their game
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

    switch (user_input) { // choose action depending on user input and call the respective functions
        case 1: {
            cout << "You inputted: " << user_input << "\n";

            Player *player = SaveLoad::loadSaveFile();

            // check whether the player has passed the first monster
            if (player->getLEVEL() == 0 && player->getFLOOR() == 0) {
                // player has done its job
                delete player;

                CastleScene::playScene();
            }
            else {
                // load the lobby scene
                LobbyScene::playScene(player);
            }

        } break;
        case 2: {
            cout << "You inputted: " << user_input << "\n";
            cout << "New Game Started!!!!" << endl;

            // a new player object/ pointer will be created in the castle scene
            CastleScene::playScene();
        } break;
        case 3: {

            // use for testing new features (like combat scenes)
            cout << "You inputted: " << user_input << "\n";

            Player *player = SaveLoad::loadSaveFile();
            Monster *monster = new Monster(2);

            // cout << "Now Accessing SETTINGS";
            //SettingScene::playScene();

            CombatScene::playScene(player, monster);
        } break;
        case 4:
            cout<< "See you next time! We hope you enjoyed your stay!"<<endl;
            exit(0);
            break;
    }

}
