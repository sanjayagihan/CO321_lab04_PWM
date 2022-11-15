#include<avr/io.h>

int main(){
    DDRD |= (1<<PD6);                                   // Fast PWM output at OCOA pin
    TCNT0 = 0;                                          // Set timer0 to 0
    OCR0A = 127;                                        // Set OCR0A to 127 , set PWM duty cycle to 50%
    TCCR0A |= (1<<COM0A1) | (1<<WGM00) | (1<<WGM01);    // Set fast PWM mode
    TCCR0B = 3;                                         // Set timer0 prescaler to 64 (CS02=0,CS01=1,CS00=1)
    while(1){
    }
    return 0;
}
