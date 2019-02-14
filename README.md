# SCHOOL_PROJECT_TI_MSP430_LED-Button
Four ways to play around buttons and LEDs on TI MSP430

__This is a practice to explore the dynamics between LED and button on TI MSP430__

## Four modes of LED-Button interaction
* model1: If button is not pressed, red LED blinks. If button keeps being pressed, green LED blinks.
* model2: If button is not pressed, red LED continues on. If button keeps being pressed, green LED on.
* model3: Red LED changes state upon each button press. A sample sequence could be like this: LED on -> press button -> LED off -> press button -> LED on -> press button -> LED off -> ...
* model4: Red and green LED changes state alternatively upon button press. E.g. Red LED on -> press button -> Red LED off -> press button -> Green LED on -> press button -> Green LED off -> ...

## How to use
The four modes are written as functions, and their functions calls are all included in the main function. Comment out the three function calls that are undesired and test the uncommented one. If more than one function calls are left uncommented, the behavior has not been tested and could be __disastrous__.
