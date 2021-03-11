#include <iostream>
#include <fstream>

#include "player.h"
#include "saveLoad.h"
#include <stdlib.h>

#include "pugixml/pugixml.hpp"

using namespace std;
using namespace pugi;

const char SaveLoad::PLAYER_SAVEFILE[] = "savefile.xml";

// can be used in checking whether the continue button can be pressed
bool SaveLoad::checkSaveFileExist(const char* fileName) {
    if (FILE *file = fopen(fileName, "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

// create new save file
// taking default hp, dodge and user inputted name as input
void SaveLoad::createNewSaveFile(int newHP, int newDODGE, string newNAME) {
    // remove past save file
    if (checkSaveFileExist(PLAYER_SAVEFILE)) {
        if (remove(PLAYER_SAVEFILE) == 0) {
            cout << "Removed existing Save File successfully." << endl;
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

    // set default stats (HP, dodge, name)
    xml_node player = doc.append_child("Player");

    xml_node hp_node = player.append_child("HP");
    // set_value() takes c-string as input
    // need casting
    hp_node.append_child(node_pcdata).set_value(to_string(newHP).c_str());

    xml_node dodge_node = player.append_child("DODGE");
    dodge_node.append_child(node_pcdata).set_value(to_string(newDODGE).c_str());

    xml_node name_node = player.append_child("name");
    name_node.append_child(node_pcdata).set_value(newNAME.c_str());

    xml_node floor_node = player.append_child("FLOOR");

    // create our default wooden sword
    xml_node items_node = player.append_child("items");
    xml_node weapon_node = items_node.append_child("weapon");
    // default weapon initialized to be of id 1
    weapon_node.append_attribute("id") = 1;

    // write the xml file
    doc.save_file(PLAYER_SAVEFILE);
}

// read the savefile
void SaveLoad::loadSaveFile(xml_document &doc) {
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
