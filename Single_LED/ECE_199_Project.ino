#define BLUE_LATCH 12



/*
  Shift Register Example
 for two 74HC595 shift registers

 This sketch turns on each of the LEDs attached to two 74HC595 shift registers,
 in sequence from output 0 to output 15.

 Hardware:
 * 2 74HC595 shift register attached to pins 2, 3, and 4 of the Arduino,
 as detailed below.
 * LEDs attached to each of the outputs of the shift register

 Created 22 May 2009
 Modified 23 Mar 2010
 by Tom Igoe

 */

//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 8;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 12;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 11;


char inputString[2];

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
   pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.println("reset");
}

void loop() {
  // iterate over the 16 outputs of the two shift registers
  for (int thisLed = 0; thisLed < 32; thisLed++) {
    // write data to the shift registers:
    registerWrite(thisLed, HIGH);
    // if this is not the first LED, turn off the previous LED:
    if (thisLed > 0) {
      registerWrite(thisLed - 1, LOW);
    } 
    // if this is  the first LED, turn off the highest LED:
    else {
      registerWrite(31, LOW);
    } 
    // pause between LEDs:
    digitalWrite(13,HIGH);
    delay(300);
    digitalWrite(13,LOW);
     delay(10);
  }

}

// This method sends bits to the shift registers:

void registerWrite(int whichPin, int whichState) {
  // the bits you want to send. Use an unsigned int,
  // so you can use all 16 bits:
  static unsigned long int bitsToSend = 0;    

  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(latchPin, LOW);

  // turn on the next highest bit in bitsToSend:
  bitWrite(bitsToSend, whichPin, whichState);
  Serial.println(bitsToSend, BIN);

  // break the bits into two bytes, one for 
  // the first register and one for the second:
  byte registerOne = (bitsToSend & 0xff000000) >> 24;
  byte registerTwo = (bitsToSend & 0xff0000) >> 16;
  byte registerThree = (bitsToSend & 0xff00) >> 8;
  byte registerFour  = bitsToSend & 0xff; 
  // shift the bytes out:
  shiftOut(dataPin, clockPin, MSBFIRST, ~registerOne);
  shiftOut(dataPin, clockPin, MSBFIRST, ~registerTwo);
  shiftOut(dataPin, clockPin, MSBFIRST, ~registerThree);
  shiftOut(dataPin, clockPin, MSBFIRST, ~registerFour);

  // turn on the output so the LEDs can light up:
  digitalWrite(latchPin, HIGH);
}
