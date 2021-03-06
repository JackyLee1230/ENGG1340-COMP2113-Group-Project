#include "player.h"

using namespace std;

int Player::getHP() { return Player::HP; }

void Player::setHP(int newHP){
    Player::HP = newHP;
}

int Player::getATK(){ return Player::ATK; }

void Player::setATK(int newATK) {
    Player::ATK = newATK;
}

int Player::getDEF() { return Player::DEF; }

void Player::setDEF(int newDEF) {
    Player::DEF = newDEF;
}

string Player::getNAME() { return Player::NAME; }

string Player::setNAME(string newNAME) {
    Player::NAME = newNAME;
}
