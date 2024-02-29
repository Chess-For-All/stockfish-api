#include <iostream>
#include <string>

using namespace std;
int main(int argc, char** argv) {
    while (true) {
        char* cline;
        cin.getline(cline, 256);
        string line(cline);

        if (line.find("bestmove") != string::npos) {
            cout << line << endl;
        }
    }
    return 0;
}