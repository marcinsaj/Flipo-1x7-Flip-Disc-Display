/*----------------------------------------------------------------------------------*
 * A simple example of controlling two 1x7 flip-disc displays                       *
 * Example connection diagram: https://bit.ly/2x1x7-ARD                             *
 *                                                                                  *
 * Project website: https://bit.ly/1x7-FD                                           *
 * Marcin Saj 30 Jan 2023                                                           *
 * https://www.Flipo.io                                                             *
 *                                                                                  *
 * Arduino board with a power module or dedicated controller is required to operate *
 * the displays:                                                                    *
 * 1. Arduino board + Pulse Shaper Power Supply - https://bit.ly/PSPS-FD            *
 * 2. Or dedicated controller - https://bit.ly/AC1-FD                               *
 *----------------------------------------------------------------------------------*/

/* The library <FlipDisc.h> uses SPI to control flip-disc displays. 
The user must remember to connect the display inputs marked: 
- DIN - data in - to the MOSI (SPI) output of the microcontroller, 
- CLK - clock - input of the display to the SCK (SPI).
The displays are connected in series through the built-in connectors, 
only the first display from the left is connected to the Arduino or a dedicated controller.
 
It is very important to connect and declare EN, CH, PL pins. 
The declaration of DIN (MOSI) and CLK (SCK) is not necessary, 
because the SPI.h library handles the SPI hardware pins. */

#include <FlipDisc.h>   // https://github.com/marcinsaj/FlipDisc 

// Pin declaration for Arduino Uno and PSPS module
#define EN_PIN  10    // Start & End SPI transfer data
#define CH_PIN  8     // Charging PSPS module - turn ON/OFF
#define PL_PIN  9     // Release the current pulse - turn ON/OFF

/*
// Pin declaration for a dedicated controller
#define EN_PIN  A7
#define CH_PIN  A2 
#define PL_PIN  A3
*/

void setup() 
{
  /* FlipDisc.Pin(); it is the most important function and first to call before everything else. 
  The function is used to declare pin functions. Before starting the device, double check 
  that the declarations and connection are correct. If the connection of the control outputs 
  is incorrect, the display may be physically damaged. */
 
  FlipDisc.Pin(EN_PIN, CH_PIN, PL_PIN);
  
  /* FlipDisc.Init(display1, display2, ... display8); it is the second most important function.
  Initialization function for a series of displays. Up to 8 displays can be connected in series 
  in any configuration. The function has 1 default argument and 7 optional arguments. 
  The function also prepares SPI. Correct initialization requires code names of the serially 
  connected displays:
  - SEG - 7-segment display
  - DOTS - 2x1 or 3x1 dot display
  - FLIP3 - 1x3 display
  - FLIP7 - 1x7 display  
  Example for four FLIP7 displays: FlipDisc.Init(FLIP7, FLIP7, FLIP7, FLIP7); */
 
  FlipDisc.Init(FLIP7, FLIP7);
  delay(3000);
}

void loop() 
{
  /* The function is used to turn off (clear) all displays */
  FlipDisc.Clear();
  delay(1000);
  
  /* The function is used to turn on (set) all discs of all displays */
  FlipDisc.All();
  delay(1000);

  FlipDisc.Clear();
  delay(1000);

  /* The function allows you to control up to seven discs of the selected display. 
  FlipDisc.Flip7(moduleNumber, disc1,disc2,disc3,disc4,disc5,disc6,disc7);
  The first argument is the relative number "moduleNumber" of the display in the series 
  of all displays. For example, if we have a combination of FLIP7, SEG, FLIP7, 
  then the second FLIP7 display will have a relative number of 2 even though 
  there is a SEG display between the FLIP7 displays.
  - moduleNumber - relative number of the FLIP7 display
  - disc1, disc2, disc3, disc4, disc5, disc6, disc7 - counting from left to right 1-7 */
  
  /* Set the first and the second disc of the first display */
  FlipDisc.Flip7(1,1,1);
  delay(1000);
  
  /* Set the first three discs and reset the fourth disc of the second display */
  FlipDisc.Flip7(2,1,1,1,0);
  delay(1000);

  FlipDisc.Clear();
  delay(1000);

  /* Reset the fourth and fifth disc, set the rest of discs */
  FlipDisc.Flip7(2,1,1,1,0,0,1,1);
  delay(1000);

  FlipDisc.Clear();
  delay(1000);

  /* Function allows you to control a selected disc in a selected FLIP7 display.
  You can control only one disc of the selected display at a time.
  FlipDisc.ToFlip7(moduleNumber, discNumber, discStatus);
  The first argument moduleNumber is the relative number of the display 
  in the series of all displays. For example, if we have a combination of 
  FLIP7, SEG, FLIP7, then the second FLIP7 display will have a relative number of 2 
  even though there is a SEG display between the FLIP7 displays.
  - moduleNumber - relative number of the FLIP7 display
  - discNumber - display disc number counting from left to right 1-7
  - discStatus - reset disc "0" or set disc "1" */
  
  /* Reset the fifth disc, counting from the left of the first display, 
  counting from the left */
  FlipDisc.ToFlip7(1, 5, 0);
  delay(1000);

  FlipDisc.All();
  delay(1000);
 
 /* Reset the sixth disc of the second display */
  FlipDisc.ToFlip7(2, 6, 0);
  delay(1000);
  
  FlipDisc.Clear();
  delay(1000); 

  for (int i = 0; i < 5; i++)
  {
    for(int j = 1; j <= 7; j++)
    {
      FlipDisc.ToFlip7(1, j, 1);
      FlipDisc.ToFlip7(2, (7+1)-j, 1);
      delay(200);  
    }
    
    for(int j = 1; j <= 7; j++)
    {
      FlipDisc.ToFlip7(1, j, 0);
      FlipDisc.ToFlip7(2, (7+1)-j, 0);
      delay(200);  
    }
  }

  FlipDisc.All();
  delay(1000); 
}
