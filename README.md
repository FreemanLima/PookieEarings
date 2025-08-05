This project was started by my girlfriend in a simple workshop I gave about designing PCBs in KiCad and then programming a PIC.

The circuit is super simple, and maybe wouldnt even need an MCU, but the idea was that the projects in this workshop were simple and not very complex.

Just a simple voltage divider with and LDR connected to an analog input to the PIC12F675 and then 2 LEDs connected to output pins on the PIC.

The code reads the voltage on the LDR and outputs a proporcional PWM signal to the led depending on the brightness.

FYI THIS IS THE FIRST PIC I HAVE PROGRAMMED BESIDES BLINKING AN LED, IT IS NOT THE MOST OPTIMIZED, IT IS ALSO NOT THE PRETTIEST AND I KNOW I COULD HAVE USED INTERRUPTS FOR SOME THINGS AND THE LED STUTTERS WHEN IT POOLS THE ADC.
