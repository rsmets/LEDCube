#define RED 1
#define BLUE 2
#define GREEN 4



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
//clock, latch, data (far one)
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
  
  //Bottom Row
  pinMode(2, OUTPUT); 
  
  //Middle Row
  pinMode(3, OUTPUT);
  
  //Top Row
  pinMode(4, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("reset");
}

void loop() {
  static int thisLed;
  
  for(int color = 1; color < 8; color*=2){
  // iterate over the 16 outputs of the two shift registers
  for (thisLed = 0; thisLed < 10; thisLed+=2) {
    // write data to the shift registers:
    registerWrite(thisLed, HIGH, color);
    // if this is not the first LED, turn off the previous LED:
    if (thisLed > 0) {
      registerWrite(thisLed - 1, LOW, color);
    } 
    // if this is  the first LED, turn off the highest LED:
    else {
      registerWrite(10, LOW, color);
    } 
    // pause between LEDs:
    digitalWrite(13,HIGH);
    delay(100);
    digitalWrite(13,LOW);
    delay(100);
    
    //2= BOTTOM, 3=MIDDLE, 4=TOP
    /**digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    delay(100);
    digitalWrite(3, HIGH);
    digitalWrite(2, LOW);
    delay(1000);
    digitalWrite(4, LOW);
    delay(10);
    digitalWrite(4, HIGH);
    */
    int t=50;
    
    digitalWrite(2, HIGH);
    delay(t);
    digitalWrite(2, LOW);
    delay(t);
    digitalWrite(3, HIGH);
    delay(t);
    digitalWrite(3, LOW);
    delay(t);
    digitalWrite(4, HIGH);
    delay(t);
    digitalWrite(4, LOW);
    
    
  }
  }

}

// This method sends bits to the shift registers:

void registerWrite(int location, int whichState, int color) {
  int whichPin;
  
    // the bits you want to send. Use an unsigned int,
  // so you can use all 16 bits:
  static unsigned long int bitsToSend = 0; 
  
  if((color & RED) == RED){
 // Red Color
  if(location == 0) whichPin=9;
  else if(location < 7) whichPin = 9 + location;
  else if(location == 7) whichPin = 8;
  else if(location == 8) whichPin = 5;
  else return;
  
  // turn on the next highest bit in bitsToSend:
  bitWrite(bitsToSend, whichPin, whichState);
  Serial.println(bitsToSend, BIN);
   }

  if((color & GREEN) == GREEN){
  //Green Color
  if(location == 0) whichPin=17;
  else if(location < 7) whichPin = 17 +location;
  else if(location == 7) whichPin = 16;
  else if(location == 8) whichPin = 7;
  else return;
  
  // turn on the next highest bit in bitsToSend:
  bitWrite(bitsToSend, whichPin, whichState);
  //Serial.println(bitsToSend, BIN);
  }
  
  if((color & BLUE) == BLUE){
    //Blue
  if(location == 0) whichPin=25;
  else if(location < 7) whichPin = 25 + location;
  else if(location == 7) whichPin = 24;
  else if(location == 8) whichPin = 6;
  else return;
  
  // turn on the next highest bit in bitsToSend:
  bitWrite(bitsToSend, whichPin, whichState);
  //Serial.println(bitsToSend, BIN);
  }
  
  

  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(latchPin, LOW);


  // break the bits into two bytes, one for 
  // the first register and one for the second:
  byte registerOne = (bitsToSend & 0xff000000) >> 24;
  byte registerTwo = (bitsToSend & 0xff0000) >> 16;
  byte registerThree = (bitsToSend & 0xff00) >> 8;
  byte registerFour  = bitsToSend & 0xff; 
  // shift the bytes out:
  shiftOut(dataPin, clockPin, MSBFIRST, ~registerOne); //Blue
  shiftOut(dataPin, clockPin, MSBFIRST, ~registerTwo); //Green
  shiftOut(dataPin, clockPin, MSBFIRST, ~registerThree); //Red
  shiftOut(dataPin, clockPin, MSBFIRST, ~registerFour); // 5-Red, 6-Blue, 7-Green

  // turn on the output so the LEDs can light up:
  digitalWrite(latchPin, HIGH);
}
