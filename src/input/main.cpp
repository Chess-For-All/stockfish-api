#include <iostream>
#include <chrono>
#include <cpr/cpr.h>
#include <vector>
#include <string>

using namespace std;

void next(vector<string>& moves, string& last_next_stamp, string& next_stamp) {
    cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8080/nextmove"});
    next_stamp = r.text.substr(4);
    string move = r.text.substr(0,4);
    if (next_stamp != last_next_stamp) {
        moves.push_back(move);
    }
}

void best(vector<string>& moves, string& last_best_stamp, string& best_stamp) {
    cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8080/bestmove"});
    best_stamp = r.text.substr(4);
    string move = r.text.substr(0,4);
    if (best_stamp != last_best_stamp) {
        moves.push_back(move);
    }
}

int main() {
    cout << "ucinewgame" << endl;
    vector<string> moves;
    string last_best_stamp = "0";
    string last_next_stamp = "0";
    while (true) {
        string best_stamp, next_stamp;
        best(moves, last_best_stamp, best_stamp);
        next(moves, last_next_stamp, next_stamp);
        
        if (last_next_stamp != next_stamp) {
            cout << "position startpos moves ";

            for (string move : moves) {
                cout << move << ' ';
            }
            cout << '\n' << "go movetime 1000" << endl;
            last_best_stamp = best_stamp;
            last_next_stamp = next_stamp;
        }
        this_thread::sleep_for(2000ms);
    }
    return 0;
}