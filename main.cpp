#include "mbed.h"
#include "Stacker.h"
#include "Adafruit_LEDBackpack.h"

const int WAIT_TIME_MS = 300;   // Required delay between button presses

InterruptIn button(p22);
Stacker stacker;
Timer buttonTimer;        // Timer to record button presses
int buttonPress = 0;      // Flag for button

I2C i2c(p28,p27);
Adafruit_8x16matrix matrix(&i2c);

// Method stubs
void buttonPressed();
void setup();
void displayBoard(int currState[8][16]);


int main() {
    setup();

    // Begin loop
    while(1) {
        GameState state = stacker.getGameState();
        if (state == Playing) {
            if (buttonPress) {
                stacker.buttonPressed();
                buttonPress = 0;
            }
            stacker.keepPlaying();
        } else if (buttonPress) {
             stacker.restart();
             buttonPress = 0;
        }

    }
}

// A function to handle setup for main
void setup() {
    matrix.begin(0x70);                     // Begin I2C connection
    matrix.setRotation(3);                  // Set matrix orientation
    stacker.attachDisplay(&displayBoard);   // Pass display function to Stacker game
    button.rise(&buttonPressed);            // Bind button press function
    buttonTimer.start();                    // Start timer
    stacker.restart();                      // Begin game
}

// A function to handle button presses
void buttonPressed() {
    // Only count press if it has been at least WAIT_TIME_MS millseconds
    if (buttonTimer.read_ms() >= WAIT_TIME_MS) {
        buttonTimer.reset();                // Set timer back to 0
        buttonPress = 1;                    // Sets flag to be used on next main() loop
    }
}


// A function that writes an array to the led matrix.
void displayBoard(int currState[8][16]) {
    matrix.clear();                         // Clear write buffer
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 16; y++) {
           if (currState[x][y] == 1)
             matrix.drawPixel(x,y,1);
        }
    }
    matrix.writeDisplay();                  // Write out to led matrix
}
