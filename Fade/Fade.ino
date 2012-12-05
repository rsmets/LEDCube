#define ON HIGH
#define OFF LOW

//clock, latch, data (loner on arduino)
const int clockPin = 11;
const int latchPin = 10;
const int dataPin = 9;

const int TOP = 6;
const int MID = 5;
const int BOT = 3;

const int RED = 1;
const int BLUE = 2;
const int GREEN = 4;

/*
 Fade
 
 This example shows how to fade an LED on pin 9
 using the analogWrite() function.
 
 This example code is in the public domain.
 FADE WORKS ON PINS 3, 5, 6, 9, 10, and 11
 */

//int led = 2;           // the pin that the LED is attached to
int brightness = 1;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  
  //Each row on the LED cube
  pinMode(BOT, OUTPUT); 
  pinMode(MID, OUTPUT);
  pinMode(TOP, OUTPUT);
  
  //LED on arduino and pin out
  pinMode(13, OUTPUT);
  
    // declare pin 9 to be an output:
  //pinMode(led, OUTPUT);
  
  Serial.begin(9600);
  //Serial.println("reset");
  
  int color = GREEN;
  registerWrite(1, ON, color, MID);
  registerWrite(2, ON, color, TOP);
  registerWrite(3, ON, color, BOT);
  registerWrite(4, ON, color, BOT);
  registerWrite(6, ON, color, BOT);
  registerWrite(7, ON, color, BOT);
  registerWrite(8, ON, color, BOT);
  registerWrite(9, ON, color, BOT);
  
  int middleCol = BLUE | GREEN | RED;
  registerWrite(5, ON, BLUE, TOP);
  //registerWrite(5, ON, middleCol, MID);
  //registerWrite(5, ON, middleCol, TOP);
  //registerWrite(5, ON, middleCol, BOT);
}




// the loop routine runs over and over again forever:
void loop()  { 
  // set the brightness of pin 9:
  brightness = 1;
  while(brightness != 0){
    analogWrite(BOT, brightness);   
  analogWrite(TOP, brightness);
  analogWrite(MID, brightness); 

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade: 
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount ; 
  }     
  // wait for 30 milliseconds to see the dimming effect    
    delay(30);   
    }
  registerWrite(5, ON, BLUE, TOP);
  delay(1000);
  registerWrite(5, OFF, BLUE, TOP);  
}





// This method sends bits to the shift registers
// PARAM: LED Locatoin (0-9), ON, OFF, RED, GREEN, BLUE
void registerWrite(int location, int whichState, int color, int row) {
  int whichPin;
  location--;
  location = location%10;
  
  rowWrite(row, whichState);
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

void rowWrite(int row, int state){
  if(state == ON){ digitalWrite(row, ON);}
   else{ digitalWrite(row, OFF); }
}
