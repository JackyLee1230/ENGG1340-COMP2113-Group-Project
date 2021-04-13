#include <iostream>
#include <string>
#include <cctype>

// exit
#include <stdlib.h>

// file.open() .close()
#include <fstream>

// system
#include <cstdlib>

#include "saveLoad.h"
#include "sceneManager.h"
#include "titleScene.h"
#include "settingScene.h"
#include "lobbyScene.h"
#include "monsterEncounterScene.h"

#include "player.h"
#include "monster.h"

using namespace std;
using namespace pugi;

//play the lobby scene where the map and rooms are shown to the player
void LobbyScene::playScene(Player *player) {

    int current_floor = player->getFLOOR();

    // load the graphics
    SceneManager::loadLobbyFloor(1);
    SceneManager::loadLobbyScreen(player);

    // Show player current status
    cout << "Player's HP: " <<  GREEN << player->getHP() << RESET << "/"
        << GREEN << player->getHP_MAX() << RESET
        << "; LEVEL = " << MAGENTA << player->getLEVEL() << RESET << endl;

    string input = "";
    getline(cin, input);

    while(true){
        // prompt for player input until input is valid
        if ((input.length() !=1) || (isdigit(input[0]) == 0) || (std::stoi(input) <= 0) || (std::stoi(input) >= 7)) {
            cout << "PLEASE ENTER CHOICE BETWEEN 1 - 6" << endl;
        }
        else {
            int user_input = std::stoi(input);

            if (user_input >= 6){
                break;
            }

            // check whether the player beated the previous monster before
            if (player->getLEVEL() < user_input) {
                // not supposed to have access to that room
                cout << "You cannot enter this room." << endl
                    << "This Room is protected with a spell" << endl
                    << "Fight the previous monsters before entering !!" << endl;
            }
            else
                break;
        }

        getline(cin, input);
     }

    int user_input = std::stoi(input);
    switch (user_input) {
        case 1: {
            // load scene
            Monster *monster = new Monster(user_input + 1);
            MonsterEncounterScene::playScene(player, monster);
        }
            break;
        case 2: {
            Monster *monster = new Monster(user_input + 1);
            MonsterEncounterScene::playScene(player, monster);
        }
            break;
        case 3: {
            Monster *monster = new Monster(user_input + 1);
            MonsterEncounterScene::playScene(player, monster);
        }
            break;
        case 4: {
            Monster *monster = new Monster(user_input + 1);
            MonsterEncounterScene::playScene(player, monster);
        }
            break;
        case 5: {
            cout << "Now Accessing the LEVEL BOSS!!!" << endl;
            cout << "Prepare for CHAOS!" << endl;
            Monster *monster = new Monster(user_input + 1);
            MonsterEncounterScene::playScene(player, monster);
        }
            break;
        case 6: {
            system("clear");
            cout<< "See you next time! We hope you enjoyed your stay!"<<endl;
            exit(0);
            }
        break;

    }

}
