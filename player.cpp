#include <iostream>

// file.open() .close()
#include <fstream>

// remove()
#include <cstdio>

// dynamic array for inventory
#include <vector>

#include "player.h"
#include "saveLoad.h"
#include "weapon.h"

// for atoi() itoa()
#include <stdlib.h>

// for reading xml
#include "pugixml/pugixml.hpp"

using namespace std;
using namespace pugi;

//const char Player::PLAYER_SAVEFILE[] = "savefile.xml";
//defauly HP_MAX value

// Input: accept default HP, Floor, LEVEL for setting player value
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

// Output: Player's HP
int Player::getHP() { return this->HP; }

// Input: new int HP value
// Set Player's HP
void Player::setHP(int newHP){
    Player::HP = newHP;
}

// Output: Player's Max HP
int Player::getHP_MAX() { return this->HP_MAX; }

// Input: New int Max HP value
// set Player's Max HP
void Player::setHP_MAX(int newHPMax){
    this->HP_MAX = newHPMax;
}

// Output: update the maximum HP according to the progress of the player
void Player::updateNewHP_MAX() {
    this-> HP_MAX = 30 + this->LEVEL * 10;
}

// Output: Player's Dodge
int Player::getDODGE(){ return this->DODGE; }

// Input: new int Dodge value
// Set Player's Dodge
void Player::setDODGE(int newDODGE) {
    Player::DODGE = newDODGE;
}

// Output: Player's Floor Level
int Player::getFLOOR() { return this->FLOOR; }

// Input: new int Floor value
// set Player's Floor level
void Player::setFLOOR(int newFLOOR){
    this->FLOOR = newFLOOR;
}

// Output: Player's LEVEL value
int Player::getLEVEL() { return this->LEVEL; }

// Output: new int LEVEL value
// set Player's level
void Player::setLEVEL(int newLEVEL) {
    this->LEVEL = newLEVEL;
}

// Output: vector of Player's Fruits
vector<Fruit> Player::getFruits() { return this->fruits; }

// Input: vector of new fruits of the player
// set Player's Fruits
void Player::setFruits(vector<Fruit> newFruits) {
    this->fruits = newFruits;
}

// Input: vector of new weapons of the player
// set the weapon of the player using a vector
void Player::setWeapons(std::vector<Weapon> weapons) {
    this->weapons = weapons;
}

// Output: vector of Player's Weapons
// get the player weapon from the vector member
std::vector<Weapon> Player::getWeapons() { return this->weapons; }
