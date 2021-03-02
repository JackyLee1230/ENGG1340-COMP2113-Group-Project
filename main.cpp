#include <iostream>
#include <fstream>
#include <string>

#include "loadScene.h"

using namespace std;

int main(){
    loadScene("start");
    loadMonsterScene("monster_boss");
    loadScene("end");
}
