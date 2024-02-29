#include <iostream>
#include <string>

using namespace std;
int main(int argc, char** argv) {
    while (true) {
        string line;

        cin >> line;

        if (line.find("bestmove") != string::npos) {
            cout << line << endl;
        }
    }
    return 0;
}