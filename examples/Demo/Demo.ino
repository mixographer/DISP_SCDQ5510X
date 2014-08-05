/* 
 Demo for Osram 4-Character 5x5 Dot Matrix Display library
 Copyright 2013 Patrik Thalin
 http://www.thalin.se
 
 The following Osram display devices are supported:
 * SCDQ5541X (Yellow)
 * SCDQ5542X (Super-red),
 * SCDQ5543X (Green)
 * SCDQ5544X (High Efficiency Green)
 
 Default connections:
 Pin 1 (LOAD) on the display to pin 2 on the Arduino.
 Pin 2 (SDATA) on the display to pin 3 on the Arduino.
 Pin 3 (SDCLK) on the display to pin 4 on the Arduino.
 Pin 4 (Vcc) on the display to 5 Volt on the Arduino.
 Pin 5 (GND) on the display to GND on the Arduino.
  
 For details on usage see:
 http://www.thalin.se/2013/03/arduino-library-for-osram-scdq554xx.html
 
*/

#include <DispSCDQ554xx.h>

// Pin connections
const int loadPin  = 2;
const int sdataPin = 3;
const int sdclkPin = 4;

// Define symbols
/* Lower 5 bits in each byte is the pixels. 
 * Other bits are ignored but set to the adress for consistency with the datasheet.
 * SCDQ_SYMBOL is a macro that pack data to 25 bits in a 32 bit variable.
 * Datasheet: http://www.thalin.se/2013/03/arduino-library-for-osram-scdq554xx.html
 */
unsigned long pn[] = { 
// ROW           0     1     2     3     4     Symbol
  SCDQ_SYMBOL(0x0e, 0x33, 0x55, 0x79, 0x8e), //0
  SCDQ_SYMBOL(0x04, 0x2c, 0x44, 0x64, 0x8e), //1
  SCDQ_SYMBOL(0x1e, 0x21, 0x46, 0x68, 0x9f), //2
  SCDQ_SYMBOL(0x1e, 0x21, 0x4e, 0x61, 0x9e), //3
  SCDQ_SYMBOL(0x06 ,0x2a, 0x5f, 0x62, 0x82), //4
  SCDQ_SYMBOL(0x1f, 0x30, 0x5e, 0x61, 0x9e), //5
  SCDQ_SYMBOL(0x06, 0x28, 0x5e, 0x71, 0x8e), //6
  SCDQ_SYMBOL(0x1f, 0x22, 0x44, 0x68, 0x88), //7
  SCDQ_SYMBOL(0x0e, 0x31, 0x4e, 0x71, 0x8e), //8
  SCDQ_SYMBOL(0x0e, 0x31, 0x4f, 0x62, 0x8c), //9
  SCDQ_SYMBOL(0x00, 0x20, 0x40, 0x6c, 0x8c), //.
  SCDQ_SYMBOL(0x0f, 0x30, 0x53, 0x71, 0x8f)  //G
  };

DispSCDQ554xx Disp(loadPin, sdataPin, sdclkPin);

void setup() {
  Disp.begin();
}

void loop() {
  // Write pos 0
  for(int k=0; k <= 9; k++){
    Disp.write(0, pn[k]);
    delay(400);
  }
  
  // Clear all
  Disp.clear();
  delay(700);
  
  // Write all positions with rotations
  for(int rot=0; rot <= 4; rot++){
    for(int k=0; k <= 4; k++){
      Disp.write(k, pn[k], rot);
    }
    delay(700);
  }  
  delay(700);
  
  // Brightness
  Disp.setBrightness(2);
  delay(700);
  Disp.setBrightness(6);
  delay(700);
  
  // Clear one position
  for(int k=0; k <= 4; k++){
    Disp.clear(k);
    delay(700);
  }
  
  // Write ....
  for(int k=0; k <= 4; k++){
    Disp.write(k, pn[10]);
  }
  
  // Sleep & Wake
  delay(700);
  Disp.sleep();
  delay(700);
  Disp.wake();
  delay(700);
  
  // Clear all
  Disp.clear();
  delay(700);
}
