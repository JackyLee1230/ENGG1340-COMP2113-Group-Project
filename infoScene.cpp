#include <iostream>
#include <string>

#include "sceneManager.h"
#include "titleScene.h"
#include "infoScene.h"

using namespace std;

// Input: -
// Output: load the Info scene
// and return the main menu when player input "n"
void InfoScene::playScene() {
    SceneManager::loadInfoScreen();

    string user_input = "";

    getline(cin, user_input);

    // user input check to determine game action
    while (true) {
        if (user_input.length() == 1) {
            if (user_input == "n")
                break;
        }

        getline(cin, user_input);
    }

    TitleScene::playScene();

}
