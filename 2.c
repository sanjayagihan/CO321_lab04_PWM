#include<avr/io.h>


void blink_ms_delay(){                                  
    TCNT1 = 0;                                          // Set timer1 to 0
    TCCR1A = 0;                                         // Set timer1A to to normal mode
    TCCR1B = 2;                                         // Set timer1 prescaler to 64 (CS12=0,CS11=1,CS10=0)
    while((TIFR1&0x01)==0);                             // Wait until timer1 overflow flag is set
    TCCR1A = 0;                                         // Reset
    TCCR1B = 0;                                         // Reset
    TIFR1 = 0x01;                                       // Clear timer1 overflow flag
}

void fadeLED(int value){
    TCNT0 = 0;                                          
    OCR0A = value;                                      // Set OCR0A to value , change PWM duty cycle
    TCCR0A |= (1<<COM0A1) | (1<<WGM00) | (1<<WGM01);    // Set fast PWM mode and non-inverting mode
    TCCR0B = 3;                                         // Set timer0 prescaler to 64 (CS02=0,CS01=1,CS00=1)
}

int main(){
    DDRD |= (1<<PD6);                                   // Fart PWM output at OCOA pin
    int brightness = 0;                                 // Set brightness to 0
    int fadeAmount = 5;                                 // Set fadeAmount to 5
    while(1){
        fadeLED(brightness);                            // Call fadeLED function, fade LED
        brightness += fadeAmount;                       // Increase brightness by fadeAmount
        if(brightness == 0 || brightness == 255){       // If brightness is 0 or 255
            fadeAmount = -fadeAmount;                   // Change fadeAmount to negative
        }
        blink_ms_delay();                               // call the blink_ms_delay function
    }
    return 0;
}
