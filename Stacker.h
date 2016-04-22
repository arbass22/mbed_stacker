#include "mbed.h"

enum GameState { Playing, Lost, Won };
typedef enum GameState GameState;

class Stacker {
    public:
        Stacker();
        void attachDisplay(void (*display)(int[][16]));
        void buttonPressed();
        void restart();
        GameState getGameState();
        void keepPlaying();
    private:
        void printBoard();
};
