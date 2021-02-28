#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// read .txt and then output
void loadScene(string scenes) {
    string scene = scenes + ".txt";
    string line;
    ifstream myfile (scene);
    if (myfile.is_open()){
        while (getline (myfile,line)){
          cout << line << '\n';
        }
        cout<< endl;
    myfile.close();
    }
}

int main(){
  loadScene("start");
  return 0;
}
