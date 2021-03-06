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

using namespace std;

void TitleScene::playScene() {
    // load the graphics
    SceneManager::loadTitleScreen();


    string input = "";
    cin >> input;

    //user_input = std::stoi(temp);

    // TODO
    // input check
    while(input.length() !=1 || isdigit(input[0]) == 0 ){
      while (std::stoi(input) <= 0 || std::stoi(input) >= 5) {
          cin >> input;
          cout <<"success";
          // cout << user_input << "\n";
      }
    }

    int user_input = std::stoi(input);
    Monster test = Monster("gatekeeper");
    switch (user_input) {

        case 1: {
            cout << "You inputted: " << user_input << "\n";

            system("clear");
            test.loadAsciiArt("monster_2");
            cout << test.getHP() << " " << test.getATK() << " " << test.getDEF() << " " << test.getNAME() << endl;

        } break;
        case 2:
            cout << "You inputted: " << user_input << "\n";
            break;
        case 3:
            cout << "You inputted: " << user_input << "\n";
            system("clear");
            cout << "Now Accessing SETTINGS";
            break;
        case 4:
            exit(0);
            break;
    }

}
