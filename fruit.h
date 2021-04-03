// fruit.h
#ifndef FRUIT_H
#define FRUIT_H

#include "pugixml/pugixml.hpp"

#include "player.h"
class Player;

enum FruitID {
    APPLE = 1,
    PEAR,
    GRAPE,
    DRAGONS_FRUIT,
    PEACH
};

class Fruit {
private:

    FruitID fruit_id;
    int HP;
    std::string NAME;
    int DODGE;
    int QUANTITY;

public:

    static const char FRUIT_STATS_FILE[];

    Fruit(int);

    std::string getNAME();

    int getID();

    int getHP();

    void showFRUITS();

    int getDODGE();

    int act(Player *);

    void loadFruitXML(pugi::xml_document&);
};

#endif
