// implementation of SceneManager
// seperate interface and implementation

#include <iostream>
#include <fstream>
#include <string>

#include "sceneManager.h"
#include "titleScene.h"
#include "lobbyScene.h"
#include "settingScene.h"
#include "monster.h"
#include "player.h"
#include "weapon.h"

using namespace std;

// for printing coloured text (for HP and other stuff)
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define VICTORY "\xE2\x9C\x8C"
#define WARNING "\xE2\x9A\xA0"
#define BOSS "\xF0\x9F\x98\x88"
#define SPARKLE "\xE2\x9D\x87"

// width:height = 16:9
const int SceneManager::SCENE_WIDTH = 80;
const int SceneManager::SCENE_HEIGHT = 45;

const string SceneManager::SCENES_FOLDER_PATH = "scenes_art/";

// filenames for defined scenes
const string SceneManager::TITLE_SCENE = "title";
const string SceneManager::INVENTORY_SCENE = "inventory";
const string SceneManager::LOBBY_SCENE = "lobby";
const string SceneManager::FLOOR_SCENE = "floor";
const string SceneManager::END_SCENE = "end";
const string SceneManager::MAIN_SCENE = "mainmenu";
const string SceneManager::COMBAT_SCENE = "combat";
const string SceneManager::SETTING_SCENE = "setting";
const string SceneManager::CASTLE_SCENE = "castle";
const string SceneManager::COMBAT_WIN_SCENE = "combat_win";
const string SceneManager::COMBAT_LOSE_SCENE = "combat_lose";

// return the number of leading space to center align the text
// int SceneManager::calculateLeftJustify(int string_width) {
//     return (SceneManager::SCENE_WIDTH - string_width) / 2;
// }


// load the title screen
void SceneManager::loadTitleScreen() {
    string file_name = TITLE_SCENE + ".txt";
    string line;

    ifstream myfile (SCENES_FOLDER_PATH + file_name);

    system("clear");

    // load the specific scene only
    if (myfile.is_open()) {
        while (getline (myfile, line)) {
            cout << line << '\n';
        }
        cout << endl;
    }

    myfile.close();
}

// load the castle scene and background text
void SceneManager::loadCastleScreen() {
    string file_name = CASTLE_SCENE + ".txt";
    string line;

    ifstream myfile (SCENES_FOLDER_PATH + file_name);

    system("clear");

    // load the specific scene only
    if (myfile.is_open()) {
        while (getline (myfile, line)) {
            cout << line << '\n';
        }
        cout << endl;
    }

    myfile.close();
}

// load the Lobby screen
void SceneManager::loadLobbyScreen() {
    string file_name = LOBBY_SCENE + ".txt";
    string line;

    ifstream myfile (SCENES_FOLDER_PATH + file_name);

    // load the specific scene only
    int n=0;
    if (myfile.is_open()) {
        while (getline (myfile, line)) {
            cout << line << '\n';
            n++;
        }
        cout << endl;
    }

    myfile.close();
}

//load the lobby floor scene of the player level/floor
void SceneManager::loadLobbyFloor(int floor_no) {
    string file_name = "floor_" + to_string(floor_no) + ".txt";
    string line;

    ifstream myfile (SCENES_FOLDER_PATH + file_name);

    system("clear");

    // load the specific scene only
    if (myfile.is_open()) {
        while (getline (myfile, line)) {
            cout << line << '\n';
        }
        cout << endl;
    }

    myfile.close();
}

//load the ASCII Art of the Monster player is fighting
void SceneManager::loadEncouterMonster(int monster_ID){
    string file_name = "monster_" + to_string(monster_ID) + ".txt";
    string line;
    Monster monster = Monster(monster_ID);
    ifstream myfile (SCENES_FOLDER_PATH + file_name);

    system("clear");

    monster.loadAsciiArt("monster_" + to_string(monster_ID));
    // load the specific scene only
    if (myfile.is_open()) {
        while (getline (myfile, line)) {
            cout << line << '\n';
        }
        cout << endl;
    }

    myfile.close();
}

//load the combat screen with the player and monster pointer, together with description of the player and monster actions
void SceneManager::loadCombatScreen(Player *player, Monster *monster, string player_action_des, string monster_action_des) {

    // screen cleaning
    system("clear");

    cout << "> " << player_action_des << endl;

    // print with the value of HP being green
    printf("Player\tHP: " GREEN "%d" RESET " / " GREEN "%d" RESET "\t\n",
        player->getHP(), player->HP_MAX
    );
    cout << "\n\n";

    cout << "> " << monster_action_des << endl;

    printf("%s\tHP: " GREEN "%d" RESET " / " GREEN "%d" RESET,
        monster->getNAME().c_str(), monster->getHP(), monster->getHP_MAX()
    );

    // load shieldHP if shieldHP not equal to 0
    if (monster->getSHIELDHP() > 0) {
        printf("\tShield: < HP: " BLUE "%d" RESET ", Type: " BLUE "%s" RESET " >",
            monster->getSHIELDHP(),
            monster->getSHIELD_ISMAGIC() ? "MAGIC" : "PHYSICAL"
        );
    }

    cout << "\n";

    // division line
    for (int i = 0; i < SCENE_WIDTH / 2; i++)
        cout << "x=";
    cout << endl;

    // get the weapons of the player
    std::vector<Weapon> weapons = player->getWeapons();
    for (int i = 0; i < weapons.size(); i++) {
        cout << "[" << (i+1) << "] "; // show the weapon id before stats for debugging
        weapons[i].showWeapon();
        cout << endl;
    }
    cout << endl;
}

//load the scene if either the player died or killed the monster
void SceneManager::loadCombatResultScreen(bool isPlayerWon) {
    string file_name = "";
    string line;

    // showing different screen according to
    // whether the player won or lose the battle
    if (isPlayerWon) {
        file_name = COMBAT_WIN_SCENE + ".txt";
    }
    else if (!isPlayerWon){
        file_name = COMBAT_LOSE_SCENE + ".txt";
    }

    ifstream myfile (SCENES_FOLDER_PATH + file_name);

    system("clear");

    if(myfile.is_open()) {
        while (getline(myfile, line)) {
            cout << line << "\n";
        }
        cout << endl;
    }

    myfile.close();
}

//load the setting screen
void SceneManager::loadSettingScreen(){
  string file_name = SETTING_SCENE + ".txt";
  string line;

  ifstream myfile (SCENES_FOLDER_PATH + file_name);

  system("clear");

  // load the specific scene only
  if (myfile.is_open()) {
      while (getline (myfile, line)) {
          cout << line << '\n';
      }
      cout << endl;
  }

  myfile.close();
}
