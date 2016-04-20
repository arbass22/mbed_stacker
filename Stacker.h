#include "mbed.h"

class Stacker {
    public:
        Stacker();
        void attachDisplay(void (*display)(int[][16]));
        void buttonPressed();
        void restart();
};
