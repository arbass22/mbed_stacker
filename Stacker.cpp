#include "Stacker.h"

int currState[8][16]= {};       // Curr game board
void (*displayFunc)(int[][16]);  // Stored function for displaying board externally
int currLevel = 0;
int currDirection = 0;

/**
*   The constructor for the stacker game.
*/
Stacker::Stacker() {
    // Initialize to empty board
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 16; j++) {
            currState[i][j] = 0;
        }
    }
    currState[1][2] = 1;

}

/**
*   Gives the stacker object a function that it can use to display the board state
*/
void Stacker::attachDisplay(void (*display)(int[][16])) {
    displayFunc = display;
}


/**
    Signals to the game that the user pressed the button.
*/
void Stacker::buttonPressed() {
    printf("Stacker Button Pushed\r\n");
    displayFunc(currState);
}
