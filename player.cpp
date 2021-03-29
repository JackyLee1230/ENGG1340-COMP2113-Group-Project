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
const int Player::HP_MAX = 30;

Player::Player(int newHP, int newDODGE, int newFLOOR) {
    // // get items and set a dynamic size array to store that items
    // int n = 0; // number of weapons owned by the player
    // for (xml_node weapon = player.child("items").child("weapon"); weapon; weapon = weapon.next_sibling("weapon"))
    //     n++;

    this-> HP = newHP;
    this-> DODGE = newDODGE;
    this-> FLOOR = newFLOOR;

    // cout << "Call from player's constructor" << endl;
    // cout << "Player's HP = " <<  HP << "; DODGE = " << DODGE << "; FLOOR = " << FLOOR << endl;

    // building the weapon inventory for combat scene
}

int Player::getHP() { return Player::HP; }

void Player::setHP(int newHP){
    Player::HP = newHP;
}

int Player::getFLOOR() { return Player::FLOOR; }

void Player::setFLOOR(int newFLOOR){
    Player::FLOOR = newFLOOR;
}


int Player::getATK(){ return Player::ATK; }

void Player::setATK(int newATK) {
    Player::ATK = newATK;
}

int Player::getDODGE(){ return Player::DODGE; }

void Player::setDODGE(int newDODGE) {
    Player::DODGE = newDODGE;
}

// int Player::getDEF() { return Player::DEF; }
//
// void Player::setDEF(int newDEF) {
//     Player::DEF = newDEF;
// }

// string Player::getNAME() { return Player::NAME; }
//
// string Player::setNAME(string newNAME) {
//     Player::NAME = newNAME;
// }

void Player::setWeapons(std::vector<Weapon> weapons) {
    this->weapons = weapons;
}

std::vector<Weapon> Player::getWeapons() { return this->weapons; }
