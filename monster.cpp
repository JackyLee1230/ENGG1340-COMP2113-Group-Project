#include <iostream>
#include <fstream>
#include <string>

#include "monster.h"

using namespace std;

const string Monster::MONSTER_ART_FOLDER_PATH = "monsters_art/";

int Monster::getHP() { return HP; }

void Monster::setHP(int newHP){
    HP = newHP;
}

int Monster::getATK(){ return ATK; }

void Monster::setATK(int newATK){
    ATK = newATK;
}

int Monster::getDEF() { return DEF; }

void Monster::setDEF(int newDEF){
    DEF = newDEF;
}

// int Monster::calculateHP(int HP){
//     return float(HP) * level * 1.3;
// }
//
// int Monster::calculateATK(float ATK){
//     return float(ATK) * level * 1.3;
// }
//
// int Monster::calculateDEF(int DEF){
//     return float(DEF) * level * 1.3;
// }

std::string Monster::getNAME() { return NAME; }

std::string Monster::setNAME(std::string newNAME){
    NAME = newNAME;
}

// load the monster art
// similar to loadTitleScreen
void Monster::loadAsciiArt(string fileName) {
    string file_name = fileName + ".txt";
    string line;

    ifstream myfile (MONSTER_ART_FOLDER_PATH + file_name);

    // load the specific scene only
    if (myfile.is_open()) {
        while (getline (myfile, line)) {
            cout << line << '\n';
        }
        cout << endl;
    }

    myfile.close();
}
