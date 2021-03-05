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
<<<<<<< b9048421f3de79d2ebbdc79629f29274d56e4e0c
    while(input.length() !=1)// input check
=======
    while(input.length() !=1){// input check
>>>>>>> Auto stash before revert of "Changed algorithm for choice input"
      while (std::stoi(input) <= 0 or std::stoid(input) >= 5) {
          cin >> input;
          // cout << user_input << "\n";
      }
    }

<<<<<<< b9048421f3de79d2ebbdc79629f29274d56e4e0c
    int user_input = std::stoi(input)
=======
    int user_input = std::stoi(input);
>>>>>>> Auto stash before revert of "Changed algorithm for choice input"
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
