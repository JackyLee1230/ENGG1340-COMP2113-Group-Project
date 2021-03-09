// player.h
#ifndef PLAYER_H
#define PLAYER_H

class Player {
  private:
      int HP;
      int ATK;
      int DEF;
      std::string NAME;
      int DODGE;

  public:
    int getHP();

    void setHP(int newHP);

    int getATK();

    void setATK(int newATK);

    int getDODGE();

    void setDODGE(int newDODGE);

    int getDEF();

    void setDEF(int newDEF);

    std::string getNAME();

    std::string setNAME(std::string newNAME);

    static void loadStatsFromSave();

    static void saveStats();

};

#endif
