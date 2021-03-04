#include "player.h"

using namespace std;

int Player::getHP() { return Player::HP; }

void setHP(int newHP){
    Player::HP = newHP;
}

int getATK(){ return Player::ATK; }

void setATK(int newATK) {
    Player::ATK = newATK;
}

int getDEF() { return Player::DEF; }

void setDEF(int newDEF) {
    Player::DEF = newDEF;
}

string getNAME() { return Player::NAME; }

string setNAME(string newNAME) {
    Player::NAME = newNAME;
}
