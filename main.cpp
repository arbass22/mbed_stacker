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


int main() {
    setup();
   // I2C i2c(p28,p27);
    matrix.begin(0x70);
    matrix.setRotation(3);
   // matrix.writeDisplay();
    //matrix.begin(0x70);



    while(1) {

    }
}

void setup() {
    set_time(1);    // Must set time for time() to return a value
    stacker = Stacker();
    button.rise(&buttonPressed);
    lastPress = time(NULL);
}

void buttonPressed() {
    matrix.clear();

    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 8; x++) {
            matrix.drawPixel(x,y,1);
            matrix.writeDisplay();
            wait(.005);
        }
    }
    time_t newTime = time(NULL);    // Gets current time (in sec)
    if ((newTime - lastPress) >= WAIT_TIME) {
        // Only count press if it has been at least WAIT_TIME seconds
        lastPress = newTime;
        stacker.buttonPressed();
    }
}
