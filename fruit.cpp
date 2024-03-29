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

//constructor for creating a fruit, using the Fruit ID and quantity
// Input: int Fruit ID, quantity
// Output: create a Fruit obj with value read from XML
Fruit::Fruit(int fruitID, int quantity) {

    // load the weapon's stats from xml doc
    xml_document doc;
    Fruit::loadFruitXML(doc);

    // get the weapon that we wanna load
    xml_node fruit = doc.find_child_by_attribute("fruit", "id", to_string(fruitID).c_str());

    // get stats and others
    fruit_id = static_cast<FruitID>(fruitID);
    NAME = fruit.child("name").child_value();
    HP = atoi(fruit.child("HP").child_value());
    this->QUANTITY = quantity;
}

//member functions to access and set the stats of the fruits

// Input: -
// Output: get Fruit's ID
int Fruit::getID() {
    return static_cast<int>(this->fruit_id);
}

// Input: -
// Output: get Fruit's Name
string Fruit::getNAME() { return this->NAME; }

// Input: -
// Output: get Fruit's Hp healing
int Fruit::getHP() { return this->HP; }

// Input: -
// Output: get Fruit's quantity
int Fruit::getQUANTITY() { return this->QUANTITY; }

// Input: new int Quantity value
// Output: update the quantity of that fruit
void Fruit::setQUANTITY(int newQuantity) {
    this->QUANTITY = newQuantity;
}

// Input: accept player pointers
// Output: use a Fruit in the player inventory
// remove 1 fruit and heal the player
// using a fruit to heal the player and print out the action
int Fruit::act(Player *player){

    //heal the player by the the fixed amount from the consumable
    if(this->HP + player->getHP() > player->getHP_MAX()){
        player->setHP(player->getHP_MAX());
    }else{
        player->setHP( player->getHP() + int(this->HP) );
    }

    this->QUANTITY--;

    // no more item left, remove that item from the list of available items
    if(this->QUANTITY == 0){
        return 1;
    // there are still remaining item(s)
    }else{
        return 0;
    }
}

// Input: -
// Output: Load the Fruit from XMl file
// output error in loading if any
// load the fruits stats from the weapon_stats XML file
// output whether there is an error or not in reading the stats
void Fruit::loadFruitXML(xml_document& doc) {
    // load the xml first
    xml_parse_result result = doc.load_file(FRUIT_STATS_FILE);

    // quick check whether we load the file successfully or not
    // if (result) {
    //     std::cout << "XML [" << FRUIT_STATS_FILE << "] parsed without errors" << endl;
    // }
    // else {
    //     std::cout << "XML [" << FRUIT_STATS_FILE << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
    //     std::cout << "Error description: " << result.description() << "\n";
    //     std::cout << "Error offset: " << result.offset << " (error at [..." << (FRUIT_STATS_FILE + result.offset) << "]\n\n";
    // }
}

// Input: Vector element function
// Output: show all fruits in player inventory
void Fruit::showFruit() {
    fprintf(stdout, "%-16s%4s< HEALING: %3dHP, QUANTITY: %2d >",
        this->NAME.c_str(),
        "",
        this->HP,
        this->QUANTITY
    );
}
