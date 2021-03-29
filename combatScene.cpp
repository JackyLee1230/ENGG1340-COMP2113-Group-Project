#include "combatScene.h"
#include "monster.h"
#include "skills.h"
#include "lobbyScene.h"
#include "SceneManager.h"
#include "player.h"
#include "titleScene.h"
#include "settingScene.h"
#include "saveLoad.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

#include "pugixml/pugixml.hpp"

using namespace std;
using namespace pugi;

// should pass the player's and monster's detail
void CombatScene::playScene(Player *player, Monster *monster) {

    // load the graphics
    SceneManager::loadCombatScreen(player, monster);

}

void CombatScene::MonsterMove(Monster *monster, monster_ID) {
    // Randomly choose monster's move
    int monster_move =  rand()%(monster.getSKILLHIGH() - monster.getSKILLLOW() + 1) + monster.getSKILLLOW();
    Skill skill = new Skill(monster_move);
    cout << "Monster " << monster.getNAME() <<  " casted: " << skill.getNAME() << " and dealt " << skill.getATK() << " damage";
    cout << "End of Monster's Turn!" << endl;
    cout << "Time for you to fight back! Warrior!" << endl;

}

void CombatScene::PlayerMove(Player *player) {
    //ask for player input for action
    string input = "";
    cin >> input;

    while(input.length() !=1 || isdigit(input[0]) == 0 || std::stoi(input) <= 0 || std::stoi(input) >= 7){
        cout << "PLEASE ENTER CHOICE BETWEEN 1 - 4" << endl;
        cin >> input;
     }

    int user_input = std::stoi(input);
    switch (user_input) {
        case 1: {
            cout << "Using Weapon 1 to attack!";
            }
            break;
        case 2: {
            cout << "Using Weapon 2 to attack!";
            }
            break;
        case 3:{
            cout << "Using Weapon 3 to attack!";
            }
            break;
        case 4:{
            cout << "Using Weapon 4 to attack!";
            }
            break;
    }

}
