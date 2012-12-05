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
  

}

// Cube arrangment with location of LED if look upon from above and the shift registers were to the left
//  9 | 8 | 7
//  6 | 5 | 4
//  3 | 2 | 1


// the loop routine runs over and over again forever:
void loop()  { 
  int static x = 1;
  int static y = 0;
  if(x==10) {y++;x=1;}
  if(y%3==0){
  registerWrite(x, ON, color, BOT);
  delay(100);
  registerWrite(x, OFF, color, BOT);
  }
  else if(y%3==1){
  registerWrite(x, ON, color2, MID);
  delay(100);
  registerWrite(x, OFF, color2, MID);
  }
  else if(y%3==2){
  registerWrite(x, ON, color3, TOP);
  delay(100);
  registerWrite(x, OFF, color3, TOP);
  }
  
  x++;
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
