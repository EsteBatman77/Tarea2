#include "mbed.h"
#include <iostream>
#include "TextLCD.h"
#include "TecladoLib.h"


DigitalIn rowPins[4] = {PTE19, PTE18, PTE17, PTE16};
DigitalOut colPins[3] = {PTE6, PTE5, PTE4};

Teclado teclado(rowPins, colPins);
TextLCD lcd(D2, D3, D4, D5, D6, D7,TextLCD::LCD116x2);

string printlcd (){
    bool flag = true;
    char key;
    string text = "";
    lcd.locate(0,1);
    while(flag){
        key = teclado.leerTeclado();
        if(key == '#')
            flag = false;
        else if(key == '*'){
            lcd.locate(0,1);
            lcd.printf("                "); 
            lcd.locate(0,1);
        }else{
            lcd.printf("%c",key);
            text += key;
        }
    }
    wait_us(1000000);
    return text;
}

void showMessage(string msg){
    lcd.cls();
    for(int i = 0; msg[i] != '\0'; i++){
        lcd.locate(0, i);
        lcd.putc(msg[i]);
        wait_us(500000);
    }
    wait_us(1000000);
} 

void showMessageWithNumber(string msg, float number){
    lcd.cls();
    int i;
    for(i = 0; msg[i] != '\0'; i++){
        lcd.locate(i, 0);
        lcd.putc(msg[i]);
        wait_us(500000);
    }
    lcd.locate(i++, 0);
    lcd.printf("%.4f", number);
} 


#include "mbed.h"
#include "TecladoLib.h"
#include "LCDLib.h" // Asegúrate de incluir la librería LCD

Teclado teclado(rowPins, colPins, keys);
LCD lcd; // Crea un objeto LCD

void uno(char key) {
    double x1, y1, x2, y2;
    string sx1, sx2, sy2, sy1;
    double m, b;
    bool flag = true;

    lcd.clear(); // Limpia la pantalla LCD

    while (flag) {
        lcd.setCursor(0, 0);
        lcd.print("Ingrese X1:");
        key = teclado.leerTeclado();
        while (key != '#') {
            key = teclado.leerTeclado();
            sx1 += key;
        }
        x1 = std::stod(sx1);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Ingrese Y1:");
        key = teclado.leerTeclado();
        while (key != '#') {
            key = teclado.leerTeclado();
            sy1 += key;
        }
        y1 = std::stod(sy1);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Ingrese X2:");
        key = teclado.leerTeclado();
        while (key != '#') {
            key = teclado.leerTeclado();
            sx2 += key;
        }
        x2 = std::stod(sx2);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Ingrese Y2:");
        key = teclado.leerTeclado();
        while (key != '#') {
            key = teclado.leerTeclado();
            sy2 += key;
        }
        y2 = std::stod(sy2);

        if (x1 == x2) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("La pendiente es");
            lcd.setCursor(1, 0);
            lcd.print("indeterminada.");
        } else {
            m = (y2 - y1) / (x2 - x1);
            b = y1 - (m * x1);

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Pendiente:");
            lcd.setCursor(1, 0);
            lcd.print(m);
            lcd.setCursor(2, 0);
            lcd.print("Intercepto Y:");
            lcd.setCursor(3, 0);
            lcd.print(b);
        }
        flag = false;
    }
}

int promedio(const std::vector<int>& temperaturas) {
    int suma = 0;
    for (int elemento : temperaturas) {
        suma += elemento;
    }
    return suma / temperaturas.size();
}

int devEstandar(const std::vector<int>& temperaturas) {
    int promedio_temperaturas = promedio(temperaturas);
    int sumaDiferenciasCuadradas = 0;

    for (int elemento : temperaturas) {
        int diferencia = elemento - promedio_temperaturas;
        sumaDiferenciasCuadradas += diferencia * diferencia;
    }

    int desviacionEstandar = std::sqrt(static_cast<double>(sumaDiferenciasCuadradas) / temperaturas.size());
    return desviacionEstandar;
}

void dos(char key) {
    string selemento;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ingrese la cantidad");
    lcd.setCursor(1, 0);
    lcd.print("de temperaturas:");
    key = teclado.leerTeclado();
    int n = key - '0';

    std::vector<int> temperaturas(n);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ingrese temperaturas");
    lcd.setCursor(1, 0);
    lcd.print("separadas por '#':");

    for (int &elemento : temperaturas) {
        while (key != '#') {
            key = teclado.leerTeclado();
            if (key != '#') {
                selemento += key;
            }
        }
        elemento = std::stoi(selemento);
        selemento = "";
    }

    int promedio_temperaturas = promedio(temperaturas);
    int desviacion_estandar = devEstandar(temperaturas);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Promedio:");
    lcd.setCursor(1, 0);
    lcd.print(promedio_temperaturas);
    lcd.setCursor(2, 0);
    lcd.print("Desv. Estándar:");
    lcd.setCursor(3, 0);
    lcd.print(desviacion_estandar);
}

int hexaDeci(const std::string& nHex) {
    int nDeci = 0;
    int base = 16;
    
    for (int i = nHex.size() - 1, exp = 0; i >= 0; i--, exp++) {
        char digit = nHex[i];

        if (isdigit(digit)) {
            nDeci += (digit - '0') * pow(base, exp);
        } else if (isalpha(digit)) {
            // (A=10, B=11, ..., F=15)
            nDeci += (toupper(digit) - 'A' + 10) * pow(base, exp);
        } else {
            // Error 
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Caracter no valido");
            lcd.setCursor(1, 0);
            lcd.print("en el hex: ");
            lcd.setCursor(2, 0);
            lcd.print(digit);
            return -1;
        }
    }
    return nDeci;
}

void tres() {
    PwmOut red(LED1);
    PwmOut green(LED2);
    PwmOut blue(LED3);

    string hex;
    float pwmR = 0.0;
    float pwmG = 0.0;
    float pwmB = 0.0;

    char key = '\0';

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ingrese el código");
    lcd.setCursor(1, 0);
    lcd.print("hexadecimal:");

    while (key != '#') {
        key = teclado.leerTeclado();
        if (key != '#' && isxdigit(key)) {
            hex += key;
        }
    }

    if (hex.length() != 6) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("El código debe tener");
        lcd.setCursor(1, 0);
        lcd.print("6 caracteres.");
    } else {
        string hexR = hex.substr(0, 2);
        string hexG = hex.substr(2, 2);
        string hexB = hex.substr(4, 2);

        pwmR = hexaDeci(hexR);
        pwmG = hexaDeci(hexG);
        pwmB = hexaDeci(hexB);

        pwmR /= 255.0;
        pwmG /= 255.0;
        pwmB /= 255.0;

        red.write(1.0 - pwmR);
        green.write(1.0 - pwmG);
        blue.write(1.0 - pwmB);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("LEDs configurados:");
        lcd.setCursor(1, 0);
        lcd.print("Hex: ");
        lcd.print(hex);
    }
}

int main() {
    while (true) {
        char key = teclado.leerTeclado();
        if (key != NO_KEY) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Tecla presionada:");
            lcd.setCursor(1, 0);
            lcd.print(key);
            if (key == '1') {
                uno(key);
            }
            if (key == '2') {
                dos(key);
            }
            if (key == '3') {
                tres();
            }
        }
    }
    return 0;
}
