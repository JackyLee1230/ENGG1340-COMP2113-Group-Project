#include <iostream>
#include <fstream>
#include <string>

// for clear console screen
// so that new things appear on top
#include <cstdlib>

#include "titleScene.h"
#include "sceneManager.h"
#include "LobbyScene.h"
#include "player.h"
#include "monster.h"
#include "settingScene.h"

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

    // SceneManager::loadTitleScreen();
    TitleScene::playScene();
    //LobbyScene::playScene();

}
