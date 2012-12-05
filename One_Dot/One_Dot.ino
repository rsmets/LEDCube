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

char inputString[2];

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
  
  Serial.begin(9600);
  //Serial.println("reset");
}

void loop() {
  // pause between LED:
  //digitalWrite(13,ON);
  //delay(10);
  //digitalWrite(13,OFF);
  //delay(10);
  
  int t = 75;
  int loc = 1;
  int color1 = GREEN | BLUE | RED;
  int color2 = GREEN;
  
  registerWrite(loc+3, OFF, color1, MID);
  registerWrite(loc, ON, color1, BOT);
  registerWrite(5, ON, color2, BOT);
  //registerWrite(loc+1, OFF, GREEN, MID);
  //registerWrite(loc+2, OFF, RED, TOP);
  delay(t);
  
  registerWrite(loc, OFF, color1, BOT);
  registerWrite(loc+1, ON, color1, MID);
  registerWrite(5, OFF, color2, BOT);
  registerWrite(5, ON, color2, MID);
  //registerWrite(loc+2, OFF, RED, TOP);
  delay(t);
  
  //registerWrite(loc, OFF, BLUE, BOT);
  registerWrite(loc+1, OFF, color1, MID);
  registerWrite(loc+2, ON, color1, TOP);
  registerWrite(5, ON, color2, TOP);
  registerWrite(5, OFF, color2, MID);
  delay(t);
  
  registerWrite(loc+5, ON, color1, MID);
  registerWrite(loc+2, OFF, color1, TOP);
  registerWrite(5, OFF, color2, TOP);
  registerWrite(5, ON, color2, MID);
  delay(t);
  
  registerWrite(loc+8, ON, color1, BOT);
  registerWrite(loc+5, OFF, color1, MID);
  registerWrite(5, OFF, color2, MID);
  registerWrite(5, ON, color2, BOT);
  delay(t);
  
  registerWrite(loc+7, ON, color1, MID);
  registerWrite(loc+8, OFF, color1, BOT);
  registerWrite(5, OFF, color2, BOT);
  registerWrite(5, ON, color2, MID);
  delay(t);
  
  registerWrite(loc+6, ON, color1, TOP);
  registerWrite(loc+7, OFF, color1, MID);
  registerWrite(5, OFF, color2, MID);
  registerWrite(5, ON, color2, TOP);
  delay(t);
  
  registerWrite(loc+3, ON, color1, MID);
  registerWrite(loc+6, OFF, color1, TOP);
  registerWrite(5, OFF, color2, TOP);
  delay(t);
  
  
  /*for(int color = 1; color < 8; color*=2){
  // iterate over the 16 outputs of the two shift registers
    for (thisLed = 0; thisLed < 10; thisLed+=4) {
      // write data to the shift registers:
      registerWrite(thisLed, ON, color, BOT);
      // if this is not the first LED, turn off the previous LED:
      if (thisLed > 0) {
        registerWrite(thisLed - 4, OFF, color, BOT);
      } 
      // if this is  the first LED, turn off the highest LED:
      else {
        registerWrite(10, OFF, color, BOT);
      } 
      // pause between LEDs:
      digitalWrite(13,ON);
      delay(100);
      digitalWrite(13,OFF);
      delay(100);
    }
  }*/
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
