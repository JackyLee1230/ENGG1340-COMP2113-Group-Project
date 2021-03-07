// implementation of SceneManager
// seperate interface and implementation

#include <iostream>
#include <fstream>
#include <string>

#include "sceneManager.h"
#include "monster.h"
#include "titleScene.h"
#include "settingScene.h"

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
const string SceneManager::SETTING_SCENE = "setting";
const string SceneManager::CASTLE_SCENE = "castle";

// return the number of leading space to center align the text
// int SceneManager::calculateLeftJustify(int string_width) {
//     return (SceneManager::SCENE_WIDTH - string_width) / 2;
// }
// load the castle scene and background text
void SceneManager::loadCastleScreen() {
    string file_name = CASTLE_SCENE + ".txt";
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

void SceneManager::loadEncouterMonster(int monster_ID){
    string file_name = "monster_" + to_string(monster_ID) + ".txt";
    string line;
    Monster test = Monster(monster_ID);
    ifstream myfile (SCENES_FOLDER_PATH + file_name);
    test.loadAsciiArt("monster_" + to_string(monster_ID));
    // load the specific scene only
    if (myfile.is_open()) {
        while (getline (myfile, line)) {
            cout << line << '\n';
        }
        cout << endl;
    }

    cout << "Monster: "<< test.getNAME() << " " <<test.getHP() << " " << test.getATK() << " " << test.getDEF() << endl;
    cout << "Enter 'n' to continue and fight " + test.getNAME();
    string cont_input;
    cin >> cont_input;
    if (cont_input == "n"){
      cout<<"You have chosen to fight " + test.getNAME() + "! Prepare yourself!";
    }

    myfile.close();
}

void SceneManager::loadSettingScreen(){
  string file_name = SETTING_SCENE + ".txt";
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
