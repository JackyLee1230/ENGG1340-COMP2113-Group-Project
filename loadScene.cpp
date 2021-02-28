#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const START_SCENE = "start";
const END_SCENE = "end";

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
