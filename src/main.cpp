#include <restinio/all.hpp>
#include <iostream>
#include <string>

void start(char* engine_exec, char* input_exec, char* output_exec) {
    char cmd[1000];
    strcpy(cmd, input_exec);
    strcat(cmd, " | ");
    strcat(cmd, engine_exec);
    strcat(cmd, " | ");
    strcat(cmd, output_exec);
    system(cmd);
}

void convertFEN(std::string FEN, char board[8][8]) {
    int index = 0;
    for (int y = 7; y >= 0; y--) {
        int empty;
        for (int x = 0; x < 8; x++) {
            parsechar:
            char current = FEN.at(index);
            bool filled = false;
            // std::cout << x << y << std::endl;
            switch (current) {
                case 'k': case 'q': case 'r': case 'b': case 'n': case 'p':
                case 'K': case 'Q': case 'R': case 'B': case 'N': case 'P':
                    board[y][x] = current;
                    filled = true;
                    index++;
                    // std::cout << current;
                    break;
            }
            if (!filled) {
                // std::cout << "hi" << std::endl;
                switch (current) {
                    case '1': case '2' : case '3': case '4':
                    case '5' : case '6': case '7': case '8':
                        int i;
                        for (i = 0; i < (current - '0'); i++) {
                            // std::cout << i << std::endl;
                            board[y][x+i] = ' ';
                        }
                        x += i;
                        index++;
                        break;
                    case '/':
                        index++;
                        goto parsechar;
                        break;
                }
            }
        }
    }
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            std::cout << board[y][x];
        }
        std::cout << '\n';
    }
}

int main() {
    /*restinio::run(
        restinio::on_this_thread()
            .port(8080)
            .address("localhost")
            .request_handler([](auto req) {
                return req->create_response().set_body("Hello, World!").done();
    }));*/
    char board[8][8];
    convertFEN("rnbqkbnr/pppppppp/8/8/2Kp3n/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", board);
    return 0;
}