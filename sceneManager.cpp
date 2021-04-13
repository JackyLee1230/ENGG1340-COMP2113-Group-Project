// implementation of SceneManager
// seperate interface and implementation

#include <iostream>

// for setfill() and setwidth()
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "sceneManager.h"
#include "titleScene.h"
#include "lobbyScene.h"
#include "settingScene.h"
#include "monster.h"
#include "player.h"
#include "weapon.h"
#include "fruit.h"

using namespace std;

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
void SceneManager::loadLobbyScreen(Player* player) {
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

    std::vector<string> rooms = {"Library", "Armory", "Guard Room", "Chapel" ,"Grand Hall"};
    //print out the map and the rooms that the player can go
    // and show which boss the player has and has not defeated.
    // also print out the map and the order of the rooms the player have to follow
    cout << "=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x" << endl;
    for(int i = 1; i <= 5; i++){
        if( player->getLEVEL() > i ){
            fprintf(stdout, "[%1i] %-10s %2s< Boss Status: %1s >  ",
                i,
                rooms[i-1].c_str(),
                "",
                DEFEATED //display the emoji to indicate that the boss was defeated
            );
        }else{
            fprintf(stdout, "[%1i] %-10s %2s< Boss Status: %1s>  ",
                i,
                rooms[i-1].c_str(),
                "",
                BOSS //display the emoji to indicate that the boss has not been defeated
            );
        }
        if(i % 2 ==0){
            cout << endl;
        }
    }
    cout << "[6] Quit  " << endl;
    cout << "=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x" << endl;

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
void SceneManager::loadEncouterMonster(Monster *monster){

    int monster_ID = monster->getID();

    string file_name = "monster_" + to_string(monster_ID) + ".txt";
    string line;
    ifstream myfile (SCENES_FOLDER_PATH + file_name);

    // calculate leading spaces to print the name of moster at center
    int num_of_leading_spaces = (SCENE_WIDTH - monster->getNAME().length()) / 2;
    system("clear");

    // load the name of the monster
    cout << "+" << string(SCENE_WIDTH - 2, '-')  << "+" << endl;
    cout << string(num_of_leading_spaces, ' ') << monster->getNAME() << endl;
    cout << "+" << string(SCENE_WIDTH - 2, '-')  << "+" << endl;

    monster->loadAsciiArt("monster_" + to_string(monster_ID));
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

    cout << player_action_des << endl;

    // print with the value of HP being green
    printf("Player\tHP: " GREEN "%d" RESET " / " GREEN "%d" RESET "\t\n",
        player->getHP(), player->getHP_MAX()
    );
    cout << "\n\n";

    cout << monster_action_des << endl;

    vector<int> skill_dmgs;
    int min, max;

    vector<Skill>::iterator skill_itr;
    for (skill_itr = monster->getSkills().begin(); skill_itr != monster->getSkills().end(); skill_itr++) {
        if((*skill_itr).getType() == 0){
            skill_dmgs.push_back((*skill_itr).getATK());
        }
    }

    sort(skill_dmgs.begin(), skill_dmgs.end());
    min = skill_dmgs[0];
    max = skill_dmgs[skill_dmgs.size() - 1];

    // show the damage range of the monster as well
    // only show it once if the min and max damage is the same
    if(min == max){
        printf("%s\tHP: " GREEN "%d" RESET " / " GREEN "%d" RESET RED "\tDamage Range: %d" RESET,
            monster->getNAME().c_str(), monster->getHP(), monster->getHP_MAX(), min
        );
    }else{
        printf("%s\tHP: " GREEN "%d" RESET " / " GREEN "%d" RESET RED "\tDamage Range: %d - %d" RESET,
            monster->getNAME().c_str(), monster->getHP(), monster->getHP_MAX(), min, max
        );
    }
    // printf("%s\tHP: " GREEN "%d" RESET " / " GREEN "%d" RESET,
    //         monster->getNAME().c_str(), monster->getHP(), monster->getHP_MAX() );


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
        cout << "[" << (i+1) << "] "; // show hint for user input
        weapons[i].showWeapon();
    }
    cout << endl;

    std::vector<Fruit> fruits = player->getFruits();
    for (int i = 0; i < fruits.size(); i++) {
        cout << "[" << (i+5) << "] "; // show hint for user input
        fruits[i].showFruit();
        cout << endl;
    }
    cout << endl;

}

// scene for end game once player has defeated the final boss of the game
void SceneManager::loadEndGameScreen(){
    string file_name = END_SCENE + ".txt";
    string line;

    ifstream myfile (SCENES_FOLDER_PATH + file_name);

    system("clear");

    // load the end game scene only
    if (myfile.is_open()) {
        while (getline (myfile, line)) {
            cout << line << '\n';
        }
        cout << endl;
    }

    myfile.close();

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
