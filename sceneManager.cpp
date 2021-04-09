// implementation of SceneManager
// seperate interface and implementation

#include <iostream>

// for setfill() and setwidth()
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

#include "sceneManager.h"
#include "titleScene.h"
#include "lobbyScene.h"
#include "settingScene.h"
#include "monster.h"
#include "player.h"
#include "weapon.h"
#include "fruit.h"

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
#define DEFEATED "\xE2\x9C\x94"
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
                DEFEATED
            );
        }else{
            fprintf(stdout, "[%1i] %-10s %2s< Boss Status: %1s>  ",
                i,
                rooms[i-1].c_str(),
                "",
                BOSS
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

    cout << "> " << player_action_des << endl;

    // print with the value of HP being green
    printf("Player\tHP: " GREEN "%d" RESET " / " GREEN "%d" RESET "\t\n",
        player->getHP(), player->getHP_MAX()
    );
    cout << "\n\n";

    cout << "> " << monster_action_des << endl;

    vector<int> skill_dmg ;
    int min, max;

    for(int i = monster->getSKILLLOW(); i < monster->getSKILLHIGH(); i++ ){
        Skill skill = monster->getSkills()[i];
        if(skill.getATK() != 0 && skill.getType() == 0){
            skill_dmg.push_back(skill.getATK());
        }
    }

    min = skill_dmg[0]; max = min;
    for(int i = 0 ; i < skill_dmg.size() ; i++){
        if (skill_dmg[i] > max){
            max = skill_dmg[i];
        }
        if (skill_dmg[i] < min){
            min = skill_dmg[i];
        }
    }
    
    //show the damage range of the monster as well
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
