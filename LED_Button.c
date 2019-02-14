#include <msp430.h> 
#include "msp430g2553.h"
int sw2=0;

void model1(int sw2){
    // toggle red LED when button not pushed, otherwise toggle green LED
    if (sw2 == BIT3){         // if SW2 is high (button not pushed)
         P1OUT &= ~BIT6;       // set P1.6 output as 0, leaving other output pins intact (especially leaving P1.3 output intact)
         P1OUT ^= BIT0;      // toggle P1.0 output (red LED)
         __delay_cycles(50000);
     }
     else{
         P1OUT &= ~BIT0;
         P1OUT ^= BIT6;      // toggle P1.6 output (green LED)
         __delay_cycles(200000);
     }
}

void model2(int sw2){
    // LED continue red when button not pushed, otherwise continue green
    if (sw2 == BIT3){         // if SW2 is high (button not pushed)
         P1OUT &= ~BIT6;       // set P1.6 output as 0, leaving other output pins intact (especially leaving P1.3 output intact)
         P1OUT |= BIT0;        // it is important to note that P1OUT = BIT0 is INCORRECT here, because this would change the P1OUT
                               // value at bit 3, thus disabling the push button. Must do an OR to preserve all the other bits in
                               // P1OUT to preserve the value at bit 3.
     }
     else{
         P1OUT &= ~BIT0;
         P1OUT |= BIT6;
     }
}

void model3(int sw2){
    // toggle red LED upon each button push
    P1OUT &= ~BIT6;     // make sure green LED is always off
    if (sw2 != BIT3){   // push button
        P1OUT ^= BIT0;
        __delay_cycles(200000); // prevent switch bounce
    }
}

int model4(int sw2, int currLED){
    // upon each button push, toggle red LED first (green LED off), then toggle green LED (red LED off).
    if (sw2 != BIT3){
        if (currLED == BIT0){   // toggling red LED now
            P1OUT &= ~BIT6;
            P1OUT ^= BIT0;
        }
        else if (currLED == BIT6){ // toggling green LED now
            P1OUT &= ~BIT0;
            P1OUT ^= BIT6;
        }
        if ((P1OUT & (BIT0 | BIT6)) == 0) // both LEDs are off, need to switch the LED to toggle. Note that since bit AND has lower precedence than ==, an extra parenthesis is needed to allow bit AND to execute first before ==
            currLED = (currLED == BIT0) ? BIT6 : BIT0;
        __delay_cycles(200000); // prevent switch bounce
    }
    return currLED;
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer

    P1DIR  = 0x00;              // Port 1 all inputs
    P1DIR  |= (BIT0 | BIT6);                 // Port 1.0 and 1.6 outputs for the LEDs
    P1REN |= BIT3;              // Activate resister on P1.3 (this is the push button)
    P1OUT |= BIT3;              // Make it pull up. Because SW2 asserts a 0 (active low)
    int currLED = BIT0;             // for use in model4, representing the current LED that has been toggling

    for(;;)
    { sw2 = P1IN;                   // read the port1
      sw2 &= BIT3;              // mask out only BIT 3 where SW2 is connected
      
      /* Following are function calls for the four modes of LED-Button interaction
         Leave target function call uncommented and the others commented to test
         the target mode.
      */
      //model1(sw2);
      //model2(sw2);
      //model3(sw2);
      currLED = model4(sw2, currLED);

    }
}
