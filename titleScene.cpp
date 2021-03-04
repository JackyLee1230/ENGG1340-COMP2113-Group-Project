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

    int user_input = -1;

    // TODO
    // input check
    while (true) {
        cin >> user_input;
        // cout << user_input << "\n";

        if (user_input >= 0 && user_input < 5)
            break;
    }


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
