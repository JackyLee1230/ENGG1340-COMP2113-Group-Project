class Player{
  private:
      int HP;
      int ATK;
      int DEF;
      std::string NAME;

  public:
    int getHP() { return HP; }

    void setHP(int newHP){
        HP = newHP;
    }

    int getATK(){ return ATK; }

    void setATK(int newATK){
        ATK = newATK;
    }

    int getDEF() { return DEF; }

    void setDEF(int newDEF){
        DEF = newDEF;
    }

    std::string getNAME() { return NAME; }

    std::string setNAME(std::string newNAME){
      NAME = newNAME;
    }

};
