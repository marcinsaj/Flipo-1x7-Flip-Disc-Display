/*----------------------------------------------------------------------------------*
 * A simple example of controlling one 1x7 flip-disc display                        *
 * Example connection diagram: https://bit.ly/1x1x7-ARD                             *
 *                                                                                  *
 * Project website: https://bit.ly/1x7-FD                                           *
 * Marcin Saj 30 Jan 2023                                                           *
 * https://www.Flipo.io                                                             *
 *                                                                                  *
 * Arduino board with a power module or dedicated controller is required to operate *
 * the display:                                                                    *
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
  /* Flip.Pin(); it is the most important function and first to call before everything else. 
  The function is used to declare pin functions. Before starting the device, double check 
  that the declarations and connection are correct. If the connection of the control outputs 
  is incorrect, the display may be physically damaged. */
  Flip.Pin(EN_PIN, CH_PIN, PL_PIN);
  
  /* Flip.Init(display1, display2, ... display8) it is the second most important function. 
  Initialization function for a series of displays. Up to 8 displays can be connected in series 
  in any configuration. The function has 1 default argument and 7 optional arguments. 
  The function also prepares SPI. Correct initialization requires code names of the serially 
  connected displays:
  - D7SEG - 7-segment display
  - D2X1 - 2x1 display
  - D3X1 - 3x1 display
  - D1X3 - 1x3 display
  - D1X7 - 1x7 display 
  Example for two D1X7 displays: Flip.Init(D1X7, D1X7); */
  Flip.Init(D1X7);
  delay(3000);
}

void loop() 
{
  /* The function is used to turn off (clear) all displays */
  Flip.Clear();
  delay(1000);
  
  /* The function is used to turn on (set) all discs of all displays */
  Flip.All();
  delay(1000);

  Flip.Clear();
  delay(1000);

  /* The function allows you to control up to seven discs of the selected display. 
  Flip.Display_1x7(disc1,disc2,disc3,disc4,disc5,disc6,disc7);
  The first argument is the relative number "module_number" of the display in the series 
  of all displays. For example, if we have a combination of D1X7, D7SEG, D1X7, 
  then the second D1X7 display will have a relative number of 2 even though 
  there is a D7SEG display between the D1X7 displays.
  - module_number - relative number of the D1X7 display
  - disc1, disc2, disc3, disc4, disc5, disc6, disc7 - counting from left to right 1-7 */
  /* Set first and second disc */
  Flip.Display_1x7(1,1,1);
  delay(1000);

  Flip.Clear();
  delay(1000);

  /* Reset forth and fifth disc, set rest of discs */
  Flip.Display_1x7(1,1,1,1,0,0,1,1);
  delay(1000);

  Flip.All();
  delay(1000);

  /* Function allows you to control a selected disc in a selected D1X7 display.
  You can control only one disc of the selected display at a time.
  Flip.Disc_1x7(module_number, discNumber, discStatus);
  The first argument module_number is the relative number of the display 
  in the series of all displays. For example, if we have a combination of 
  D1X7, D7SEG, D1X7, then the second D1X7 display will have a relative number of 2 
  even though there is a D7SEG display between the D1X7 displays.
  - module_number - relative number of the D1X7 display
  - discNumber - display disc number counting from left to right 1-7
  - discStatus - reset disc "0" or set disc "1" */
  /* Reset the fifth disc, counting from the left of the first display, 
  counting from the left */
  Flip.Disc_1x7(1, 5, 0);
  delay(1000);

  /* Reset the seventh disc */
  Flip.Disc_1x7(1, 7, 0);
  delay(1000);
  
  Flip.Clear();
  delay(1000); 

  Test1();
  Test2();
  Test3();
  Test4();  
}

void Test1(void)
{
  for (int i = 0; i < 5; i++)
  {
    for(int j = 1; j <= 7; j++)
    {
      Flip.Disc_1x7(1, j, 1);
      delay(200);  
    }
    
    for(int j = 1; j <= 7; j++)
    {
      Flip.Disc_1x7(1, j, 0);
      delay(200);  
    }
  }

  Flip.All();
  delay(1000); 
}

void Test2(void)
{
  for (int i = 0; i < 5; i++)
  {
    for(int j = 1; j <= 7; j++)
    {
      Flip.Disc_1x7(1, j, 0);
      if(j == 1) Flip.Disc_1x7(1, 7, 1);
      if(j > 1) Flip.Disc_1x7(1, j-1, 1);
      delay(200);  
    }
  }

  Flip.Clear();
  delay(1000);  
}

void Test3(void)
{
  for (int i = 0; i < 5; i++)
  {
    for(int j = 1; j <= 7; j++)
    {
      Flip.Disc_1x7(1, j, 1);
      if(j == 1) Flip.Disc_1x7(1, 7, 0);
      if(j > 1) Flip.Disc_1x7(1, j-1, 0);
      delay(200); 
    }
  }

  Flip.Clear();
  delay(1000);  
}

void Test4(void)
{
  for (int i = 0; i < 5; i++)
  {
    for(int j = 1; j <= 7; j++)
    {
      Flip.Disc_1x7(1, j, 1);
      if(j > 1) Flip.Disc_1x7(1, j-1, 0);
      delay(100);  
    }
    
    for(int j = 7; j >= 1; j--)
    {
      Flip.Disc_1x7(1, j, 1);
      if(j < 7) Flip.Disc_1x7(1, j+1, 0);
      delay(100);  
    }
  }

  Flip.Clear();
  delay(1000);   
}
