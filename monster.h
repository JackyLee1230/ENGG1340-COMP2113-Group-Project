// monster.h
#ifndef MONSTER_H
#define MONSTER_H

class Monster
{
private:
    int HP;
    int ATK;
    int DEF;
    std::string NAME;

public:
    static const std::string MONSTER_ART_FOLDER_PATH;

    // Monster();

    int getHP();

    void setHP(int newHP);

    int getATK();

    void setATK(int newATK);

    int getDEF();

    void setDEF(int newDEF);

    int calculateHP(int HP);

    int calculateATK(float ATK);

    int calculateDEF(int DEF);

    std::string getNAME();

    std::string setNAME(std::string newNAME);

    void loadAsciiArt(std::string fileName);
};

#endif
