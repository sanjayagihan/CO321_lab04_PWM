/*
The frequency of the sound made by a piezo buzzer depends on the frequency of the
PWM waveform applied to it. In this case, the duty cycle affects the volume of the
sound. Write a program that repeatedly generates 4 separate sound frequencies in
increasing order one after the other. (each frequency should be heard for a notable
time before switching to the next frequency so that it can be heard properly). Keep
in mind that humans can hear frequencies in the range 20Hz - 20,000Hz only.
*/
#include<avr/io.h>

void blink_ms_delay(){                                  
    TCNT1 = 0;                                          // Set timer1 to 0
    TCCR1A = 0;                                         // Set timer1A to to normal mode
    TCCR1B = 5;                                         // Set timer1 prescaler to 1024 (CS12=1,CS11=0,CS10=1)
    while((TIFR1&0x01)==0);                             // Wait until timer1 overflow flag is set
    TCCR1A = 0;                                         // Reset
    TCCR1B = 0;                                         // Reset
    TIFR1 = 0x01;                                       // Clear timer1 overflow flag
}

void frequency(int value){
    TCNT0 = 0;                                          
    OCR0A = 127;                                        // Set OCR0A to value , change PWM duty cycle
    TCCR0A |= (1<<COM0A1) | (1<<WGM00) | (1<<WGM01);    // Set fast PWM mode and non-inverting mode
    TCCR0B = value;                                     // Set timer0 prescaler to 64 (CS02=0,CS01=1,CS00=1)
}

int main(){
    DDRD |= (1<<PD6);                                   // Fart PWM output at OCOA pin
    int prescalars[4] = {2,3,4,5};                      // Set frequencies array
    while(1){
        for(int i=0;i<4;i++){                          // Loop through frequencies array
            frequency(prescalars[i]);                  // Call frequency function, change frequency
            blink_ms_delay();                          // call the blink_ms_delay function
        }
    }
    return 0;
}


/*
(16*1000000)/(256*8)   = 
(16*1000000)/(256*64)  = 
(16*1000000)/(256*256)  = 
(16*1000000)/(256*1024) = 
*/
