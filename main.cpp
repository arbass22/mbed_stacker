#include "mbed.h"
#include "Stacker.h"
#include "Adafruit_LEDBackpack.h"

const int WAIT_TIME = 1;

InterruptIn button(p23);
Stacker stacker;
time_t lastPress;  // Time of last button press

I2C i2c(p28,p27);
Adafruit_8x16matrix matrix(&i2c);


void buttonPressed();
void setup();
void displayBoard(int currState[8][16]);


int main() {
    setup();
    stacker = Stacker();
    while(1) {

    }
}

// A function to handle setup for main
void setup() {
    matrix.begin(0x70);     // Begin I2C connection
    matrix.setRotation(3);
    set_time(1);            // Must set time for time() to return a value
    stacker.attachDisplay(&displayBoard);
    button.rise(&buttonPressed);
    lastPress = time(NULL);
}

// A function to handle button presses
void buttonPressed() {
    time_t newTime = time(NULL);    // Gets current time (in sec)
    if ((newTime - lastPress) >= WAIT_TIME) {
        // Only count press if it has been at least WAIT_TIME seconds
        lastPress = newTime;
        stacker.buttonPressed();
    }
}


// A function that writes an array to the led matrix.
void displayBoard(int currState[8][16]) {
    matrix.clear();
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 16; y++) {
           if (currState[x][y] == 1)
             matrix.drawPixel(x,y,1);
        }
    }
    matrix.writeDisplay();
}
