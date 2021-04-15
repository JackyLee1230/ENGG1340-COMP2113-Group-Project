// sceneManager.h
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "player.h"
#include "monster.h"

// for printing coloured text (for HP and other stuff)
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define VICTORY "\xE2\x9C\x8C"
#define DEFEATED "\xE2\x9C\x94"
#define WARNING "\xE2\x9A\xA0"
#define BOSS "\xF0\x9F\x98\x88"
#define SPARKLE "\xE2\x9D\x87"

// Manage all scene loading stuff
// an interface for the class SceneManager
class SceneManager
{
public:
    static const int SCENE_WIDTH;
    static const int SCENE_HEIGHT;

    // folders name
    static const std::string SCENES_FOLDER_PATH;
    static const std::string STORIES_FOLDER_PATH;

    // filenames for loading a specific scene
    static const std::string TITLE_SCENE;
    static const std::string LOBBY_SCENE;
    static const std::string FLOOR_SCENE;
    static const std::string INVENTORY_SCENE;
    static const std::string END_SCENE;
    static const std::string MAIN_SCENE;
    static const std::string COMBAT_SCENE;
    static const std::string SETTING_SCENE;
    static const std::string CASTLE_SCENE;
    static const std::string COMBAT_WIN_SCENE;
    static const std::string COMBAT_LOSE_SCENE;

    static void loadCastleScreen();

    static void loadEndGameScreen();

    static void loadTitleScreen();

    static void loadSettingScreen();

    static void loadLobbyScreen(Player*);

    static void loadLobbyFloor(int);

    static void loadInventoryScreen();

    static void loadEncouterMonster(Monster *);

    static void loadCombatScreen(Player *, Monster *, std::string, std::string);

    static void loadCombatResultScreen(bool);

    static void loadStory(Monster *);

    static int calculateLeftJustify(int);
};

#endif
