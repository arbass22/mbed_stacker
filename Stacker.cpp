#include "Stacker.h"


void (*displayFunc)(int[][16]);     // Stored function for displaying board externally
GameState gameState = Playing;      // Current game state

Timer timer;                        // Timer object for calculating movements

int currState[8][16]= {};           // Current game board
int currY = 0;                      // Current playing level (0-15)
int currDirection = 1;              // Current movement direction (1 = left, -1 = right);
int currX = 0;                      // The x-position of leftmost pixel of current moving bar
int currWidth = 4;                  // Width of current moving bar


void nextState() {
    // If moving bar at edge of board, change direction
    if (currX + currWidth == 8)
        currDirection = -1;
    else if (currX == 0)
        currDirection = 1;

    currX += currDirection;     // Move bar 1 px in current direction

    // Mash currState with the level bar to print state
    int newCurrState[8][16] = {};

    // Current state
    for (int y = 0; y < 16; y++) {
        for (int x = 0;  x < 8; x++) {
            newCurrState[x][y] = currState[x][y];
        }
    }
    // Level bar
    for (int x = 0; x < currWidth; x++) {
        newCurrState[currX + x][currY] = 1;
    }

    displayFunc(newCurrState);      // Display board to leds

}

void Stacker::keepPlaying() {
    // Check timer to see if next frame yet
    if (timer.read_ms() > 200) {
        nextState();     // Go to next state
        timer.reset();   // Reset timer to 0
    }
}

void Stacker::restart() {
    // Reset game variables
    gameState = Playing;
    currY = 0;
    currDirection = 1;
    currX = 0;
    currWidth = 4;
    timer.reset();

    // Initialize to empty board
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 16; j++) {
            currState[i][j] = 0;
        }
    }
}


/**
*   The constructor for the stacker game.
*/
Stacker::Stacker() {
    timer.start();
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

    int oldWidth = currWidth;       // Save current width for loop condition
    for (int i = 0; i < oldWidth; i++) {
        // Landed on stack or bottom row
        if (currY == 0 || currState[currX + i][currY-1] == 1) {
            currState[currX + i][currY] = 1;
        } else {  // Misaligned
            currWidth -= 1;
        }
    }
    // No more pixels in moving bar left / you lose
    if (currWidth == 0) {
        //restart();
        gameState = Lost;
        return;
    }
    currY += 1;         // Increase level
    currX = 0;          // Move bar to left side of board
    currDirection = 1;  // Start bar moving right
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
