#include "mbed.h"

class Stacker {
    public:
        Stacker();
        void buttonPressed();
    protected:
        int currState[16][8];
        int currLevel;
        int currDirection;

};
