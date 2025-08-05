

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


volatile int ADCWINDOW = 0;

void setupbits()
{
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
  GIE = 1;
}

int SenseIO()
{
  int Analog = 0;
  Analog = (ADRESH << 8) + ADRESL;
  Analog = Analog / 4;
  return Analog;
}

void __interrupt() isr(void)
{
  if (T0IF)
  {
    ADCWINDOW ++;
    T0IF = 0;
    TMR0 = 0;
  }
}

void main(void)
{
  int duty_cycle = 125;
  setupbits();
  TMR0 = 0;
  int slider = 0;
  int dir = 1; //1 up 0 down
  while (1)
  {
    if (ADCWINDOW >= 256)
    {
      GP5 = GP1 = 0;
      GO_DONE = 1;
      while (GO_DONE);
      duty_cycle = SenseIO();
      ADCWINDOW = 0;
      TMR0 = 0;
    }
    GP5 = GP1 = (TMR0 <= duty_cycle);


//    if (dir)
//    {
//      if (slider <= duty_cycle)slider = slider + (duty_cycle / 32);
//      else
//      {
//        slider = duty_cycle;
//        dir = 0;
//      }
//    } else
//    {
//      if (slider >= 0)
//      {
//        slider = slider - (duty_cycle / 32);
//      }
//      else{
//      dir = 1;
//      slider = 0;
//      }
//    }
//    
//    GP5 = GP1 = (TMR0 <= slider);

  }
  return;
}
