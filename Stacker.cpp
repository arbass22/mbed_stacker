#include "Stacker.h"

int currState[8][16]= {};       // Curr game board
void (*displayFunc)(int[][16]);  // Stored function for displaying board externally
int currY = 0;
int currDirection = 1;
int currX = 0;
int currWidth = 4;
int buttonPressed = 0;

float lastTime = 0.0;

Timer timer;

GameState gameState = Playing;



void nextState() {
    if (currX + currWidth == 8)
        currDirection = -1;
    else if (currX == 0)
        currDirection = 1;

    currX += currDirection;

    //Mash currState with the ongoing level
    int newCurrState[8][16] = {};

    // Current state
    for (int i = 0; i < 16; i++) {
        for (int j = 0;  j < 8; j++) {
            newCurrState[j][i] = currState[j][i];
        }
    }
    // Current level
    for (int i = 0; i < currWidth; i++) {
        newCurrState[currX + i][currY] = 1;
    }
    displayFunc(newCurrState);

}

void Stacker::keepPlaying() {
    if (timer.read_ms() > 400/(currY+1)) {
        nextState();
        timer.reset();   // Reset timer to 0
    }

}

void Stacker::restart() {
    currY = 0;
    currDirection = 1;
    currX = 0;
    currWidth = 4;
    timer.start();


    // Initialize to empty board
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 16; j++) {
            currState[i][j] = 0;
        }
    }
    //timer.attach(&nextState, 0.2);

}


/**
*   The constructor for the stacker game.
*/
Stacker::Stacker() {
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
    printBoard();
    //timer.detach();     // Lose the timer
    for (int i = 0; i < currWidth; i++) {
        if (currY == 0 || currState[currX + i][currY-1] == 1) {
            // Landed on stack or bottom row
            currState[currX + i][currY] = 1;
        } else {
            // Misaligned
            currWidth -= 1;
        }
    }
    if (currWidth == 0) {
        restart();
        return;
    }
    currY += 1;
    currX = 0;
    currDirection = 1;
    //timer.attach(&nextState, 0.2);

    //printf("Stacker Button Pushed\r\n");
    //displayFunc(currState);
}

void Stacker::printBoard() {
    for (int i = 15; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            printf("%d ", currState[j][i]);
        }
        printf("\r\n");
    }
    printf("\r\n");

}

GameState Stacker::getGameState() {
    return gameState;
}
