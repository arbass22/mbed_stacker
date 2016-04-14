#include "mbed.h"
#include "Stacker.h"

const int WAIT_TIME = 1;

InterruptIn button(p30);
Stacker stacker;
time_t lastPress;  // Time of last button press

void buttonPressed();
void setup();


int main() {
    setup();

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
    time_t newTime = time(NULL);
    if ((newTime - lastPress) >= WAIT_TIME) {
        lastPress = newTime;
        stacker.buttonPressed();
    }
}
