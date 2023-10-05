#include "TecladoLib.h"

Teclado::Teclado(DigitalIn *rowPins, DigitalOut *colPins)
    : rowPins_(rowPins), colPins_(colPins) {}

char Teclado::leerTeclado() {
    for (int col = 0; col < COLS; col++) {
        colPins_[col] = 0;

        for (int row = 0; row < ROWS; row++) {
            if (rowPins_[row] == 0) {
                ThisThread::sleep_for(DEBOUNCE_DELAY);
                if (rowPins_[row] == 0) {
                    colPins_[col] = 1;
                    return keys_[row][col];
                }
            }
        }

        colPins_[col] = 1;
    }

    return NO_KEY;
}

