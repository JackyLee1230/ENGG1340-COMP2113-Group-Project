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
    int QUANTITY;

public:

    static const char FRUIT_STATS_FILE[];

    Fruit(int, int);

    int getID();

    int getHP();

    std::string getNAME();

    void setQUANTITY(int);

    int getQUANTITY();

    int act(Player *);

    void showFruit();

    void loadFruitXML(pugi::xml_document&);
};

#endif
