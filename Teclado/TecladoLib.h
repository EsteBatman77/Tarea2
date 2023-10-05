#ifndef TECLADOLIB_H
#define TECLADOLIB_H

#include "mbed.h"

#define DEBOUNCE_DELAY 200ms
const int ROWS = 4;
const int COLS = 3;
const char keys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};
const char NO_KEY = '\0';

class Teclado {
public:
    Teclado(DigitalIn *rowPins, DigitalOut *colPins);
    char leerTeclado();

private:
    DigitalIn *rowPins_;
    DigitalOut *colPins_;
    char (*keys_)[COLS];
};

#endif
