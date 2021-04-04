// for atoi()
#include <stdlib.h>
#include <string>
#include <iostream>
// for fprintf()
#include <cstdio>

// for c_str() to convert string to const char[]
#include <cstring>
#include "pugixml/pugixml.hpp"

#include "player.h"
using namespace pugi;
using namespace std;

const char Fruit::FRUIT_STATS_FILE[] = "fruits_stats.xml";

Fruit::Fruit(int fruitID) {

    // load the weapon's stats from xml doc
    xml_document doc;
    Fruit::loadFruitXML(doc);

    // get the weapon that we wanna load
    xml_node fruit = doc.find_child_by_attribute("fruit", "id", to_string(fruitID).c_str());

    // get stats and others
    fruit_id = static_cast<FruitID>(fruitID);
    NAME = fruit.child("name").child_value();
    HP = atoi(fruit.child("HP").child_value());
    DODGE = atoi(fruit.child("DODGE").child_value());
}

int Fruit::getID() {
    return static_cast<int>(this->fruit_id);
}

string Fruit::getNAME() { return this->NAME; }

int Fruit::getHP() { return this->HP; }

int Fruit::getDODGE() { return this->DODGE; }


// monster damaging the player and print out the action
int Fruit::act(Player *player){
    std::vector<Fruit> fruits = player->getFRUITS();
    //heal the player by the the fixed amount from the consumable
    if(this->HP + player->getHP() > player->HP_MAX){
        player->setHP( player->HP_MAX);
    }else{
        player->setHP( player->getHP() + int(this->HP) );
    }
    QUANTITY--;
    // no more item left, remove that item from the list of available items
    if(this->QUANTITY == 0){
        return 1;
    // there are still remaining item(s)
    }else{
        return 0;
    }
}

// load the fruits stats from the weapon_stats XML file
// output whether there is an error or not in reading the stats
void Fruit::loadFruitXML(xml_document& doc) {
    // load the xml first
    xml_parse_result result = doc.load_file(FRUIT_STATS_FILE);

    // quick check whether we load the file successfully or not
    if (result) {
        std::cout << "XML [" << FRUIT_STATS_FILE << "] parsed without errors" << endl;
    }
    else {
        std::cout << "XML [" << FRUIT_STATS_FILE << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
        std::cout << "Error description: " << result.description() << "\n";
        std::cout << "Error offset: " << result.offset << " (error at [..." << (FRUIT_STATS_FILE + result.offset) << "]\n\n";
    }
}

void Fruit::showFRUITS() {
    fprintf(stdout, "%-16s%4s< HEALING: %2dHP >",
        this->NAME.c_str(),
        "",
        this->HP
    );
}