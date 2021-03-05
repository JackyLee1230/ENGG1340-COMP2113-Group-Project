#include <iostream>
#include <string>

// exit
#include <stdlib.h>

// system
#include <cstdlib>

#include "sceneManager.h"
#include "titleScene.h"
#include "monster.h"

using namespace std;

void TitleScene::playScene() {
    // load the graphics
    SceneManager::loadTitleScreen();


    string input = "";

    //user_input = std::stoi(temp);

    // TODO
    while(input.length() !=1){// input check
      while (std::stoi(input) <= 0 or std::stoid(input) >= 5) {
          cin >> input;
          // cout << user_input << "\n";
      }
    }

    int user_input = std::stoi(input);
    Monster test;
    switch (user_input) {

        case 1: {
            cout << "You inputted: " << user_input << "\n";

            system("clear");
            test.loadAsciiArt("monster_2");

        } break;
        case 2:
            cout << "You inputted: " << user_input << "\n";
            break;
        case 3:
            cout << "You inputted: " << user_input << "\n";
            break;
        case 4:
            exit(0);
            break;
    }

}
