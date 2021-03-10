#include <iostream>

// file.open() .close()
#include <fstream>

// remove()
#include <cstdio>

#include "player.h"
#include "SaveLoad.h"

// for atoi() itoa()
#include <stdlib.h>

// for reading xml
#include "pugixml/pugixml.hpp"

using namespace std;
using namespace pugi;

//const char Player::PLAYER_SAVEFILE[] = "savefile.xml";

Player::Player(bool is_continue, int newHP, int newDODGE, string newNAME) {

    // new game -> create initial stats and overwrite save file
    if(!is_continue) {
        // create new savefile and set default stats
        SaveLoad::createNewSaveFile(newHP, newDODGE, newNAME);
    }

    // get the loaded xml document
    xml_document doc;
    SaveLoad::loadSaveFile(doc);

    // get the part which stores the stats of player
    xml_node player = doc.child("Player");

    // set stats
    NAME = player.child("name").child_value();
    HP = atoi(player.child("HP").child_value());
    DODGE = atoi(player.child("DODGE").child_value());

    // get items and set a dynamic size array to store that items
    int n = 0;
    for (xml_node weapon = player.child("items").child("weapon"); weapon; weapon = weapon.next_sibling("weapon"))
        n++;

    cout << "Player's HP = " <<  HP << "; DODGE = " << DODGE << "; NAME = " << NAME << endl;
    cout << "There are " << n << " weapons in the player's inventory" << endl;
}

int Player::getHP() { return Player::HP; }

void Player::setHP(int newHP){
    Player::HP = newHP;
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

string Player::getNAME() { return Player::NAME; }

string Player::setNAME(string newNAME) {
    Player::NAME = newNAME;
}

// // can be used in checking whether the continue button can be pressed
// bool Player::checkSaveFileExist(const char* fileName) {
//     if (FILE *file = fopen(fileName, "r")) {
//         fclose(file);
//         return true;
//     } else {
//         return false;
//     }
// }
//
// // create new save file
// // taking default hp, dodge and user inputted name as input
// void Player::createNewSaveFile(int newHP, int newDODGE, string newNAME) {
//
//     // remove past save file
//     if (checkSaveFileExist(PLAYER_SAVEFILE)) {
//         if (remove(PLAYER_SAVEFILE) == 0) {
//             cout << "Removed existing savefile successfully." << endl;
//         }
//         else {
//             cout << "Error in removing existing savefile. Please do it mannually."  << endl;
//         }
//     }
//
//     // create new save file
//
//     xml_document doc;
//
//     // cannot using std::string, have to use char[]
//     char xml_header[] = R"(<?xml version="1.0"?>)";
//
//     doc.load_string(xml_header);
//
//     // set default stats (HP, dodge, name)
//     xml_node player = doc.append_child("Player");
//
//     xml_node hp_node = player.append_child("HP");
//     // set_value() takes c-string as input
//     // need casting
//     hp_node.append_child(node_pcdata).set_value(to_string(newHP).c_str());
//
//     xml_node dodge_node = player.append_child("DODGE");
//     dodge_node.append_child(node_pcdata).set_value(to_string(newDODGE).c_str());
//
//     xml_node name_node = player.append_child("name");
//     name_node.append_child(node_pcdata).set_value(newNAME.c_str());
//
//     // create our default wooden sword
//     xml_node items_node = player.append_child("items");
//     xml_node weapon_node = items_node.append_child("weapon");
//     weapon_node.append_attribute("id") = 1;
//
//     // write the xml file
//     doc.save_file(PLAYER_SAVEFILE);
// }
//
// // read the savefile
// void Player::loadSaveFile(xml_document &doc) {
//     // load the xml first
//     xml_parse_result result = doc.load_file(PLAYER_SAVEFILE);
//
//     // quick check whether we load the file successfully or not
//     if (result) {
//         cout << "XML [" << PLAYER_SAVEFILE << "] parsed without errors" << endl;
//     }
//     else {
//         cout << "XML [" << PLAYER_SAVEFILE << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
//         cout << "Error description: " << result.description() << "\n";
//         cout << "Error offset: " << result.offset << " (error at [..." << (PLAYER_SAVEFILE + result.offset) << "]\n\n";
//     }
//
// }
