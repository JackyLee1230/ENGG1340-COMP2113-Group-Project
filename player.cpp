#include <iostream>

#include "player.h"

// for atoi()
#include <stdlib.h>

// for reading xml
#include "pugixml/pugixml.hpp"

using namespace std;
using namespace pugi;

const char Player::PLAYER_SAVEFILE[] = "savefile.xml";

Player::Player(bool is_continue, string name="") {
    // new game -> create initial stats and overwrite save file
    if(is_continue) {
        // create new savefile
    }
    else {
        // get the loaded xml document
        xml_document doc;
        Player::loadSaveFile(doc);

        // get the part which stores the stats of player
        xml_node player = doc.child("Player");

        // set stats
        NAME = player.child("name").child_value();
        HP = atoi(player.child("HP").child_value());
        DODGE = atoi(player.child("DODGE").child_value());

        // get items and set a dynamic size array to store that items
        int n = 0;
        for (xml_node weapon = player.child("items").child("weapon"); weapon; weapon = weapon.next_sibling("weapon"))
            n++

        cout << "There are " << n << " weapons in the player's item" << endl;
    }
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

// read the savefile
void Player::loadSaveFile(xml_document &doc) {
    // load the xml first
    xml_parse_result result = doc.load_file(PLAYER_SAVEFILE);

    // quick check whether we load the file successfully or not
    if (result) {
        cout << "XML [" << PLAYER_SAVEFILE << "] parsed without errors" << endl;
    }
    else {
        cout << "XML [" << PLAYER_SAVEFILE << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
        cout << "Error description: " << result.description() << "\n";
        cout << "Error offset: " << result.offset << " (error at [..." << (PLAYER_SAVEFILE + result.offset) << "]\n\n";
    }

}
