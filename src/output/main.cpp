#include <iostream>
#include <string>
#include <cpr/cpr.h>

using namespace std;
int main(int argc, char** argv) {
    if (argc > 1) {
        string url(argv[1]);
    }
    string url = "http://localhost:8080";
    while (true) {
        char cline[256];
        cin.getline(cline, 256);
        string line(cline);
        while (line.empty()) {
            cin.getline(cline, 256);
            string temp(cline);
            line = temp;
        }

        if (line.find("bestmove") != string::npos) {
            string move = line.substr(9,5);
            cout << "\e[32m[stockfish]: \e[39m" << line << ':' << move << endl;
            cpr::Response r = cpr::Post(cpr::Url(url + "/api.php"), cpr::Payload({{"bestmove", move}}));
        } else {
            cout << "\e[31m[stockfish]: \e[39m \"" << line << '"' << endl;
        }
    }
    return 0;
}