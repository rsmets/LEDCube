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
}

// Cube arrangment with location of LED if look upon from above and the shift registers were to the left
//  9 | 8 | 7
//  6 | 5 | 4
//  3 | 2 | 1


// the loop routine runs over and over again forever:
void loop()  { 
  //options for CORNER = 1,3,7,9
  //options for POS = TOP, BOT
  int delayTime = 200;
  growCube(BLUE, delayTime, 3, TOP);
  growCube(GREEN, delayTime, 3, BOT);
  growCube(RED, delayTime, 1, BOT);
  growCube(BLUE | RED, 500, 7, TOP);
}


void growCube(int color, int t, int corner, int pos){
  int opp;
  if(pos == TOP) opp = BOT;
  else opp = TOP;
  
  int f1;
  int f2;
  int s1;
  int s2;
  int s3;
  int s4;
  int s5;
  
  if(corner == 1){
    f1=2;
    f2=4;
    s1=3;
    s2=6;
    s3=9;
    s4=8;
    s5=7;
  }
  else if(corner == 3){
    f1=6;
    f2=2;
    s1=9;
    s2=8;
    s3=7;
    s4=4;
    s5=1;
  }
  else if(corner == 9){
    f1=8;
    f2=6;
    s1=3;
    s2=2;
    s3=1;
    s4=4;
    s5=7;
  }
  else{
    f1=8;
    f2=4;
    s1=9;
    s2=6;
    s3=3;
    s4=2;
    s5=1;
  }
  
  
  registerWrite(corner, ON, color, pos);
  delay(t);
  registerWrite(f1, ON, color, MID);
  registerWrite(f2, ON, color, MID);
  registerWrite(5, ON, color, MID);
  delay(t);
  registerWrite(s1, ON, color, opp);
  registerWrite(s2, ON, color, opp);
  registerWrite(s3, ON, color, opp);
  registerWrite(s4, ON, color, opp);
  registerWrite(s5, ON, color, opp);
  delay(t);
  registerWrite(1, OFF, color, BOT);
  registerWrite(2, OFF, color, MID);
  registerWrite(4, OFF, color, MID);
  registerWrite(5, OFF, color, MID);
  registerWrite(3, OFF, color, TOP);
  registerWrite(6, OFF, color, TOP);
  registerWrite(7, OFF, color, TOP);
  registerWrite(8, OFF, color, TOP);
  registerWrite(9, OFF, color, TOP);
}

void growCubeBot(int color, int t){
 
  registerWrite(1, ON, color, BOT);
  delay(t);
  registerWrite(2, ON, color, MID);
  registerWrite(4, ON, color, MID);
  registerWrite(5, ON, color, MID);
  delay(t);
  registerWrite(3, ON, color, TOP);
  registerWrite(6, ON, color, TOP);
  registerWrite(7, ON, color, TOP);
  registerWrite(8, ON, color, TOP);
  registerWrite(9, ON, color, TOP);
  delay(t);
  registerWrite(1, OFF, color, BOT);
  registerWrite(2, OFF, color, MID);
  registerWrite(4, OFF, color, MID);
  registerWrite(5, OFF, color, MID);
  registerWrite(3, OFF, color, TOP);
  registerWrite(6, OFF, color, TOP);
  registerWrite(7, OFF, color, TOP);
  registerWrite(8, OFF, color, TOP);
  registerWrite(9, OFF, color, TOP);
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
