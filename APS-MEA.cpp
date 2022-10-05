
#include "mbed.h"

Serial pc(USBTX, USBRX);
 
DigitalOut IN1A(PB_4);
DigitalOut IN2A(PB_5);
PwmOut ENA(D2);

InterruptIn encoder(D7);
Ticker flipper;

int count = 0;
int RPM = 0;

void contador();
void reset();

int main() {
    pc.baud(9600);
    
    IN1A = 1;
    IN2A = 0;
    
    encoder.rise(&contador);
    flipper.attach(&reset, 5);
    
    
    float x = 6; // [0, 12, 0.5]
    float perc = x/12;
    
    while(1) {
        ENA.write(perc);
        pc.printf("\rCount so far: %d\n", count);
        pc.printf("\rRPM: %d\n", RPM);
        wait(5);
        
    }
}

void contador() {
    count ++;
}

void reset() {
    RPM = (count * 12)/30;
    count = 0;
}
 
