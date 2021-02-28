class Monster{
  private:
      int HP;
      int ATK;
      int DEF;

  public:
    int getHP() {return HP;}

    void setHP(int newHP){
        HP = newHP;
    }

    int getATK(){return ATK;}

    void setATK(int newATK){
        ATK = newATK;
    }

    int getDEF() {return DEF;}

    void setDEF(int newDEF){
        DEF = newDEF;
    }

    int calculateHP(int HP){
        return float(HP) * level * 1.3;
    }

    int calculateATK(float ATK){
        return float(ATK) * level * 1.3;
    }

    int calculateDEF(int DEF){
        return float(DEF) * level * 1.3;
    }

};
