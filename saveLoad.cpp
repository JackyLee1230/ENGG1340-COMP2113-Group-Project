#include <iostream>
#include <fstream>

#include <vector>

#include "saveLoad.h"
#include <stdlib.h>

#include "pugixml/pugixml.hpp"

#include "player.h"
#include "weapon.h"

using namespace std;
using namespace pugi;

const char SaveLoad::PLAYER_SAVEFILE[] = "savefile.xml";

// Input: -
// Output: can be used in checking whether the continue button can be pressed
// by checking whether the save file exist in the directory
bool SaveLoad::checkSaveFileExist() {
    if (FILE *file = fopen(PLAYER_SAVEFILE, "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

// Input: pointer of the player
// Output: create new save file (overwriting original file/ new file)
// taking default hp, dodge and user inputted name as input
// and save the new file as the game save
void SaveLoad::createNewSaveFile(Player *player) {
    // remove past save file
    if (checkSaveFileExist()) {
        if (remove(PLAYER_SAVEFILE) == 0) {
            // cout << "Removed existing Save File successfully." << endl;
        }
        else {
            cout << "Error in removing existing Save File. Please do it mannually."  << endl;
        }
    }

    // create new save file
    xml_document doc;

    // cannot using std::string, have to use char[]
    char xml_header[] = R"(<?xml version="1.0"?>)";

    doc.load_string(xml_header);

    // set default stats (HP, dodge)
    xml_node player_node = doc.append_child("Player");

    xml_node hp_node = player_node.append_child("HP");
    // set_value() takes c-string as input
    // need casting
    hp_node.append_child(node_pcdata).set_value(to_string(player->getHP()).c_str());

    xml_node dodge_node = player_node.append_child("DODGE");
    dodge_node.append_child(node_pcdata).set_value(to_string(player->getDODGE()).c_str());

    // game progress recording
    xml_node floor_node = player_node.append_child("FLOOR");
    floor_node.append_child(node_pcdata).set_value(to_string(player->getFLOOR()).c_str());

    xml_node level_node = player_node.append_child("LEVEL");
    level_node.append_child(node_pcdata).set_value(to_string(player->getLEVEL()).c_str());

    // get the weapons that the player have
    // and write them to the save file
    std::vector<Weapon> weapons = player->getWeapons();

    xml_node weapons_node = player_node.append_child("weapons");
    for (int i = 0; i < weapons.size(); i++) {
        xml_node weapon_node = weapons_node.append_child("weapon");
        weapon_node.append_attribute("id") = weapons[i].getID();
    }

    // get the fruits that the player have
    // and write the id and quantity to the save file as well
    std::vector<Fruit> fruits = player->getFruits();

    xml_node fruits_node = player_node.append_child("fruits");
    for (int i = 0; i < fruits.size(); i++) {
        xml_node fruit_node = fruits_node.append_child("fruit");

        xml_node id_node = fruit_node.append_child("id");
        id_node.append_child(node_pcdata).set_value(to_string(fruits[i].getID()).c_str());

        xml_node quantity_node = fruit_node.append_child("quantity");
        quantity_node.append_child(node_pcdata).set_value(to_string(fruits[i].getQUANTITY()).c_str());
    }

    // write the xml file
    doc.save_file(PLAYER_SAVEFILE);

    // output to the screen that the gameplay is saved
    cout << "Your gameplay is saved." << endl;
}


// Input: -
// Output: read the savefile to get the stats of the player and append the new stats
Player* SaveLoad::loadSaveFile() {

    xml_document doc;

    // load the xml first
    xml_parse_result result = doc.load_file(PLAYER_SAVEFILE);

    // quick check whether we load the file successfully or not
    // if (result) {
    //     cout << "XML [" << PLAYER_SAVEFILE << "] parsed without errors" << endl;
    // }
    // else {
    //     cout << "XML [" << PLAYER_SAVEFILE << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
    //     cout << "Error description: " << result.description() << "\n";
    //     cout << "Error offset: " << result.offset << " (error at [..." << (PLAYER_SAVEFILE + result.offset) << "]\n\n";
    // }

    xml_node player_node = doc.child("Player");

    // create new Player object with the needed values
    Player *player = new Player(
        atoi(player_node.child("HP").child_value()),
        atoi(player_node.child("DODGE").child_value()),
        atoi(player_node.child("FLOOR").child_value()),
        atoi(player_node.child("LEVEL").child_value())
    );

    // load weapons from xml doc
    xml_node weapons = player_node.child("weapons");

    player->setWeapons(
        SaveLoad::loadPlayerWeapons(weapons)
    );

    // load fruits from xml doc
    xml_node fruits = player_node.child("fruits");

    player->setFruits(
        SaveLoad::loadPlayerFruits(fruits)
    );

    return player;
}

// Input: player weapons xml node
// Output: load the weapons of the player using the weapons vector and return the weapon vector
std::vector<Weapon> SaveLoad::loadPlayerWeapons(xml_node items) {
    std::vector<Weapon> weapons;
    // weapons.reserve(1);

    for (xml_node item = items.child("weapon"); item; item = item.next_sibling()) {
        cout << "weapon id: " << item.attribute("id").as_int() << endl;

        Weapon weapon = Weapon(item.attribute("id").as_int());
        weapons.push_back(weapon);
    }

    return weapons;
}

// Input: player fruits xml node
// Output: load the fruits of the player using the fruits vector and return the fruits vector
std::vector<Fruit> SaveLoad::loadPlayerFruits(xml_node items) {
    std::vector<Fruit> fruits;

    for (xml_node item = items.child("fruit"); item; item = item.next_sibling()) {
        cout << "fruits id: " << atoi(item.child_value("id")) << endl;
        cout << "fruits quantity: " << atoi(item.child_value("quantity")) << endl;

        Fruit fruit = Fruit(
            atoi(item.child_value("id")),
            atoi(item.child_value("quantity"))
        );
        fruits.push_back(fruit);
    }

    return fruits;
}
