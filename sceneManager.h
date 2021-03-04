// loadScene.h
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

// Manage all scene loading stuff
// an interface for the class SceneManager
class SceneManager
{
public:
    static const int SCENE_WIDTH;
    static const int SCENE_HEIGHT;

    // filenames for loading a specific scene
    static const std::string TITLE_SCENE;
    static const std::string END_SCENE;
    static const std::string MAIN_SCENE;
    static const std::string COMBAT_SCENE;

    static void loadTitleScreen();

    // static void loadStory();

    static void loadEncouterMonster();

    // int calculateLeftJustify(int);
};

#endif
