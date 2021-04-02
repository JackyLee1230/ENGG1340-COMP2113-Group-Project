#include <iostream>

// file.open() .close()
#include <fstream>

// remove()
#include <cstdio>

// dynamic array for inventory
#include <vector>

#include "player.h"
#include "SaveLoad.h"
#include "weapon.h"

// for atoi() itoa()
#include <stdlib.h>

// for reading xml
#include "pugixml/pugixml.hpp"

using namespace std;
using namespace pugi;

//const char Player::PLAYER_SAVEFILE[] = "savefile.xml";
const int Player::HP_MAX = 30; //defauly HP_MAX value

// constructor called when creating a new game
Player::Player(int hp, int dodge, int floor, int level) {

    this-> HP = hp;
    this-> DODGE = dodge;

    // game progress purpose, current floor and current level
    this-> FLOOR = floor;
    this-> LEVEL = level;

    // remove all existing weapons from player
    // write a new default weapon (the one with id = 1)
    this-> weapons.clear();
    this-> weapons.push_back(Weapon(1));
}

//member functions to set the stats of the player and return the value when needed
int Player::getHP() { return this->HP; }

void Player::setHP(int newHP){
    Player::HP = newHP;
}

int Player::getDODGE(){ return this->DODGE; }

void Player::setDODGE(int newDODGE) {
    Player::DODGE = newDODGE;
}

int Player::getFLOOR() { return this->FLOOR; }


void Player::setFLOOR(int newFLOOR){
    this->FLOOR = newFLOOR;
}

int Player::getLEVEL() { return this->LEVEL; }

void Player::setLEVEL(int newLEVEL) {
    this->LEVEL = newLEVEL;
}

// int Player::getDEF() { return Player::DEF; }
//
// void Player::setDEF(int newDEF) {
//     Player::DEF = newDEF;
// }

// set the weapon of the player using a vector
void Player::setWeapons(std::vector<Weapon> weapons) {
    this->weapons = weapons;
}

// get the player weapon from the vector member
std::vector<Weapon> Player::getWeapons() { return this->weapons; }
