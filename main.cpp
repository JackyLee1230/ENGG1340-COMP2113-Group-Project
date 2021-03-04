#include <iostream>
#include <fstream>
#include <string>

// for clear console screen
// so that new things appear on top
#include <cstdlib>

// #include "loadScene.h"
#include "sceneManager.h"

using namespace std;

int main(){
    // loadScene("start");
    //
    // // clear screen
    // system("clear");
    //
    // loadMonsterScene("monster_boss");
    //
    // system("clear");
    //
    // loadScene("end");

    SceneManager::loadTitleScreen();
}
