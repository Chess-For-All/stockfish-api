#include <string>
#include <cstdlib>

class stockfish {
public:
    stockfish(char* engine_exec, char* input_exec, char* output_exec);
    ~stockfish();
};

stockfish::stockfish(char* engine_exec, char* input_exec, char* output_exec) {
    char cmd[1000];
    strcpy(cmd, input_exec);
    strcat(cmd, " | ");
    strcat(cmd, engine_exec);
    strcat(cmd, " | ");
    strcat(cmd, output_exec);
    system(cmd);
}

stockfish::~stockfish() {
}
