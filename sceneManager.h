// sceneManager.h
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

// Manage all scene loading stuff
// an interface for the class SceneManager
class SceneManager
{
public:
    static const int SCENE_WIDTH;
    static const int SCENE_HEIGHT;

    static const std::string SCENES_FOLDER_PATH;
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
    //static const std::string ENCOUNTER_SCENE;

    static void loadCastleScreen();

    static void loadTitleScreen();

    static void loadSettingScreen();

    static void loadLobbyScreen();

    static void loadLobbyFloor(int);

    static void loadInventoryScreen();

    static void loadEncouterMonster(int);

    static void loadCombatScreen();

    // int calculateLeftJustify(int);
};

#endif
