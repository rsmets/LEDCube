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

int color = RED;
int color2 = GREEN;
int color3 = BLUE;


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
  

  registerWrite(5, ON, color, MID);
  delay(1000);
  registerWrite(2, ON, color, MID);
  registerWrite(8, ON, color, MID);
  delay(1000);
  registerWrite(4, ON, color, MID);
  registerWrite(6, ON, color, MID);
}

// Cube arrangment with location of LED if look upon from above and the shift registers were to the left
//  9 | 8 | 7
//  6 | 5 | 4
//  3 | 2 | 1


// the loop routine runs over and over again forever:
void loop()  { 
  static int x=1;
  
  registerWrite(5, OFF, color, MID);
  registerWrite(2, OFF, color, MID);
  registerWrite(8, OFF, color, MID);
  registerWrite(4, OFF, color, MID);
  registerWrite(6, OFF, color, MID);
  
  if(x==1){
  registerWrite(5, ON, color, MID);
  registerWrite(2, ON, color3, MID);
  registerWrite(8, ON, color3, MID);
  registerWrite(4, ON, color, MID);
  registerWrite(6, ON, color, MID);
  delay(1000/4);
  registerWrite(5, OFF, color, MID);
  registerWrite(2, OFF, color3, MID);
  registerWrite(8, OFF, color3, MID);
  registerWrite(4, OFF, color, MID);
  registerWrite(6, OFF, color, MID);
  x++;
  delay(1000/4);
  }
  else if(x==2){
  registerWrite(5, ON, color2, BOT);
  registerWrite(1, ON, color3, BOT);
  registerWrite(7, ON, color2, BOT);
  registerWrite(3, ON, color2, BOT);
  registerWrite(9, ON, color3, BOT);
  delay(1000/4);
  registerWrite(5, OFF, color2, BOT);
  registerWrite(1, OFF, color3, BOT);
  registerWrite(7, OFF, color2, BOT);
  registerWrite(3, OFF, color2, BOT);
  registerWrite(9, OFF, color3, BOT);
  x++;
  delay(1000/4);
  }
  else{
  registerWrite(5, ON, color3, TOP);
  registerWrite(1, ON, color3, TOP);
  registerWrite(7, ON, color, TOP);
  registerWrite(3, ON, color, TOP);
  registerWrite(9, ON, color3, TOP);
  delay(1000/4);
  registerWrite(5, OFF, color3, TOP);
  registerWrite(1, OFF, color3, TOP);
  registerWrite(7, OFF, color, TOP);
  registerWrite(3, OFF, color, TOP);
  registerWrite(9, OFF, color3, TOP);
  x=1;
  delay(1000/4);
  }
  //delay();
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
