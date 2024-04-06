#include <iostream>
#include <chrono>
#include <cpr/cpr.h>
#include <vector>
#include <string>

using namespace std;

void next(vector<string>& moves, 
          string& last_next, 
          string& next_move, 
          bool& changed) {
    cpr::Response r = cpr::Get(cpr::Url{url});
    next_move = r.text.substr(0,4);
    if (next_move != last_next && 
        next_move.find('<') == string::npos && 
        !changed) {
        
        changed = true;
        moves.push_back(next_move);
        last_next = next_move;
    }
}

void best(vector<string>& moves, string& last_best, string& best_move, bool& changed) {
    cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8080/whitemove"});
    best_move = r.text.substr(0,4);
    if (best_move != last_best && best_move.find('<') == string::npos && !changed) {
        changed = true;
        moves.push_back(best_move);
        last_best = best_move;
    }
}

int main() {
    cout << "uci\nucinewgame\ngo movetime 1000" << endl;
    this_thread::sleep_for(1500ms);
    cout << "d" << endl;
    vector<string> moves;
    string last_best = "    ";
    string last_next = "    ";
    bool best_changed, next_changed;
    string best_move, next_move;
    while (true) {
        best(moves, last_best, best_move, best_changed);
        next(moves, last_next, next_move, next_changed);
        if (next_changed && best_changed) {
            cout << "position startpos moves ";

            for (string move : moves) {
                cout << move << ' ';
            }
            cout << '\n' << "go movetime 1000" << endl;
            next_changed = false;
            best_changed = false;
            this_thread::sleep_for(1500ms);
            cout << "d" << endl;
        }
        this_thread::sleep_for(200ms);
    }
    return 0;
}