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
//defauly HP_MAX value

// constructor called when creating a new game / retrieve from savefile
Player::Player(int hp, int dodge, int floor, int level) {

    // game progress purpose, current floor and current level
    this-> FLOOR = floor;
    this-> LEVEL = level;

    this-> HP = hp;
    this->updateNewHP_MAX();
    this-> DODGE = dodge;

    // remove all existing weapons from player
    // write a new default weapon (the one with id = 1)
    this-> weapons.clear();
    this-> weapons.push_back(Weapon(1));

    this-> fruits.clear();
}

//member functions to set the stats of the player and return the value when needed
int Player::getHP() { return this->HP; }

void Player::setHP(int newHP){
    Player::HP = newHP;
}

int Player::getHP_MAX() { return this->HP_MAX; }

void Player::setHP_MAX(int newHPMax){
    this->HP_MAX = newHPMax;
}

// update the maximum HP according to the progress of the player
void Player::updateNewHP_MAX() {
    this-> HP_MAX = 30 + this->LEVEL * 10;
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

vector<Fruit> Player::getFruits() { return this->fruits; }

void Player::setFruits(vector<Fruit> newFruits) {
    this->fruits = newFruits;
}

// set the weapon of the player using a vector
void Player::setWeapons(std::vector<Weapon> weapons) {
    this->weapons = weapons;
}

// get the player weapon from the vector member
std::vector<Weapon> Player::getWeapons() { return this->weapons; }
