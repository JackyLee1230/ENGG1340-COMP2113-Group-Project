#include <iostream>
#include <iomanip>
#include <string>

#include "storyScene.h"
#include "sceneManager.h"
#include "lobbyScene.h"

#include "player.h"
#include "monster.h"

using namespace std;

// Input: accept player and monster pointers
// Output: Show the story of the defeated monster after player won
void StoryScene::playScene(Player * player, Monster * monster) {
    SceneManager::loadStory(monster);

    // print the separation line
    for (int i = 0; i < SceneManager::SCENE_WIDTH / 2; i++)
        cout << "=x";
    cout << endl;

    // print the instruction with center alignment
    string instruction = "Press \'n\' to continue.";
    cout << string(SceneManager::calculateLeftJustify(instruction.length()), ' ') << instruction << endl;

    // get user input
    string user_input = "";

    getline(cin, user_input);

    // input check
    while (true) {
        if (user_input.length() == 1) {
            if (user_input == "n")
                break;
        }

        getline(cin, user_input);
    }


    // quit the game once the player has defeated the final BOSS
    // and display the final end game scene
    if (player->getLEVEL() == 6 && monster->getID() == 6){
        SceneManager::loadEndGameScreen();
        exit(0);
    }

    // release memory of the monster
    // allow the next monster to be created later
    delete monster;

    // after finishing the current level, go back to the lobby
    // load the lobby scene
    LobbyScene::playScene(player);
}
