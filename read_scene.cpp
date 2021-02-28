#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// read .txt and then output
int main() {
    string line;
    ifstream myfile ("monster.txt");
    if (myfile.is_open())
    {
        while (getline (myfile,line))
        {
          cout << line << '\n';
        }
    myfile.close();
    }
}
