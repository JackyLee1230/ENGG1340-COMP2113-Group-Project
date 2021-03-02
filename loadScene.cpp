#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const string START_SCENE = "start";
const string END_SCENE = "end";
const string MAIN_SCENE = "mainmenu";
const string COMBAT_SCENE = "combat";

// read .txt and then output
void loadScene(string scene_name) {
    string file_name = scene_name + ".txt";
    string line;
    ifstream myfile (file_name);
    if (myfile.is_open()) {
        while (getline (myfile, line)) {
          cout << line << '\n';
        }
        cout<< endl;
    myfile.close();
    }
}

void loadMonsterScene(string monster_name) {
    string file_name = monster_name + ".txt";
    string line;
    ifstream myfile (file_name);
    if (myfile.is_open()) {
        while (getline (myfile, line)) {
          cout << line << '\n';
        }
        cout<< endl;
    myfile.close();
    }
}
