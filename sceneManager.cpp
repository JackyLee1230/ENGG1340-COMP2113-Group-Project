// implementation of SceneManager
// seperate interface and implementation

#include <iostream>
#include <fstream>
#include <string>

#include "sceneManager.h"

using namespace std;

// width:height = 16:9
const int SceneManager::SCENE_WIDTH = 80;
const int SceneManager::SCENE_HEIGHT = 45;

const string SceneManager::SCENES_FOLDER_PATH = "scenes_art/";

// filenames for defined scenes
const string SceneManager::TITLE_SCENE = "title";
const string SceneManager::END_SCENE = "end";
const string SceneManager::MAIN_SCENE = "mainmenu";
const string SceneManager::COMBAT_SCENE = "combat";

// return the number of leading space to center align the text
// int SceneManager::calculateLeftJustify(int string_width) {
//     return (SceneManager::SCENE_WIDTH - string_width) / 2;
// }

// load the title screen
void SceneManager::loadTitleScreen() {
    string file_name = TITLE_SCENE + ".txt";
    string line;

    ifstream myfile (SCENES_FOLDER_PATH + file_name);

    // load the specific scene only
    if (myfile.is_open()) {
        while (getline (myfile, line)) {
            cout << line << '\n';
        }
        cout << endl;
    }

    myfile.close();
}
