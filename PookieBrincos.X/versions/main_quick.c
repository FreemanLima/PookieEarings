

// PIC12F675 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)



// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define _XTAL_FREQ 4000000

volatile int duty_cycle = 125;

void setupbits() {
    TRISIO5 = 0; //GPIO 5 E 1 COMO OUTPUTS, LEDS
    TRISIO1 = 0;
    TRISIO0 = 1; //GPIO 0 COMO INPUT
    ANS0 = 1; //METER EM MODO INPUT ANALOGICO
    CHS1 = CHS0 = 0; //ESCOLHER O CANAL DO ADC, NESTE CASO AN0
    VCFG = 0; //VREF DO ADC VDD
    ADFM = 1; //PARA LSB
    ADON = 1;
    T0CS = 0;
    PSA = 1;
    TMR0 = 0;
    T0IE = 1; //ENABLE TMR0 OVERFLOW FLAG
    T0IF = 0; //CLEAR FLAG
}

int SenseIO() {
    /*
    ASSUMINDO LDR 16-50
    VALORES PARA R 33k e 3V
    Min 0.98 V
    Max: 1.8 V
     AJUSTED FOR TOLERANCE MIN 0.95V AND MAX 2V
     BUT THEN WE AJUST THIS SO THAT THE DIF IS 1024 TO EASE THE CALCULATIONS
     SO THE FINAL VALUES ARE BELOW
     */
    const int min = 900;
    const int max = 1924; //const int dif = 1024;
    int inputD = 0;
    int Analog = 0;
    const int VDDs = 3;
    
    inputD = (ADRESH << 8) + ADRESL;
    Analog = (inputD * VDDs) - min;
   
    Analog = Analog / 4;

    if(Analog >= 255) {Analog = 255;}
    else if(Analog <= 1) {Analog = 1;}
    
    return Analog;
}

void main(void) {
    
    setupbits();
    TMR0 = 0;
    while (1) {
        
      if(T0IF){ 
        GO_DONE = 1;
        while (GO_DONE);
        duty_cycle = SenseIO();
        T0IF = 0;
        TMR0 = 0;
        }
      
      GPIO5 = GPIO1 = (TMR0 <= duty_cycle);
      
    }
    return;
}
