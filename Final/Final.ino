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


int s = 134; // should be bpm
int cDelay = 300;//some constant delay



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

// the loop routine runs over and over again forever:
void loop()  { 
  int delayTime = 200;
  int d = 2000;
  int start = 0;
  if(start == 0){
    countdown();//3 SECONDS 
    start++;
  }
  
  //uncomment here for full song
  tick(75, BLUE, BOT, 25); //4.5 SECONDS
  tick2(75, GREEN, TOP, 25);//3 SEDONDS
  tick2(75, BLUE, BOT, 25);//4SECONDS
  tick(75, GREEN, TOP, 20);//3.5 SECONDS
  //delay(5000);
  //multiColorUpDown(75, 190);
  multiColorUpDown(75, 48);
  multiColorUpDownR(75, 48);
  multiColorUpDown(75, 48);
  multiColorUpDownR(75, 48);
  //multiColorUpDown(75, 48);
  flash(RED);
  flash(BLUE);
  delay(2750);
  flash(BLUE);
  flash(RED);
  //delay(2750);
  bouncing(83, BLUE, GREEN); // at t-75 goes for 15 seconds
  flash(GREEN);
  flash(BLUE);
  //delay(2750);
  bouncing(83, BLUE, GREEN); // at t-75 goes for 15 seconds
  flash(BLUE);
  flash(GREEN);
  //delay(2750);
  bouncing(83, BLUE, GREEN); // at t-75 goes for 15 seconds
  flashAll();
  flashAll();
  //delay(2750);
  RotatingMerica(delayTime, 10);
  flashAll();
  flashAll();
  //delay(2750);
  RotatingMerica(delayTime, 10);
  flashAll();
  flashAll();
  //delay(2750);
  RotatingMerica(delayTime, 10);
  flashAll();
  flashAll();
  //multiColorUpDown(75, 50);
  RotatingMerica(delayTime, 10);
  flashAll();
  flashAll();
  delay(2750);
  flashAll();
  flashAll();
  delay(2750);
  /*cross(delayTime);
  bouncing(75, GREEN | BLUE | RED, GREEN | RED);
  RotatingMerica(delayTime);
  growCube(BLUE, delayTime, 3, TOP);
  growCube(GREEN, delayTime, 3, BOT);
  growCube(RED, delayTime, 1, BOT);
  growCube(BLUE | RED, delayTime, 7, TOP);*/
  //RotatingMerica2(delayTime);
}

void tick (int t, int color, int level, int loopt){
  int stopCount = 0;
  while(stopCount < loopt){//2*t * 30 at t = 75 then 4.5 SECONDS
  registerWrite(4, ON, color, level);
  delay(t);
  registerWrite(4, OFF, color, level);
  
  registerWrite(6, ON, color, level);
  delay(t);
  registerWrite(6, OFF, color, level);

  stopCount++;
  }
}

void tick2 (int t, int color, int level, int loopt){
  int stopCount = 0;
  while(stopCount < loopt){//2*t * 30 at t = 75 then 4.5 SECONDS
  registerWrite(3, ON, color, level);
  delay(t);
  registerWrite(3, OFF, color, level);
  
  registerWrite(7, ON, color, level);
  delay(t);
  registerWrite(7, OFF, color, level);

  stopCount++;
  }
}

void countdown(){//3 SECONDS
  
  registerWrite(1, ON, RED, TOP);
  registerWrite(2, ON, RED, TOP);
  registerWrite(3, ON, RED, TOP);
  registerWrite(5, ON, RED, TOP);
  registerWrite(4, ON, RED, TOP);
  registerWrite(7, ON, RED, TOP);
  registerWrite(8, ON, RED, TOP);
  registerWrite(9, ON, RED, TOP);
  delay(1000);
  allOff();
  
  registerWrite(1, ON, BLUE, TOP);
  registerWrite(2, ON, BLUE, TOP);
  registerWrite(3, ON, BLUE, TOP);
  registerWrite(5, ON, BLUE, TOP);
  registerWrite(7, ON, BLUE, TOP);
  registerWrite(8, ON, BLUE, TOP);
  registerWrite(9, ON, BLUE, TOP);
  delay(1000);
  allOff();
  
  registerWrite(2, ON, GREEN, TOP);
  registerWrite(5, ON, GREEN, TOP);
  registerWrite(8, ON, GREEN, TOP);
  delay(1000);
  allOff();
}

void allOff(){
 registerWrite(1, OFF, RED | BLUE | GREEN, BOT);
 registerWrite(2, OFF, RED | BLUE | GREEN, MID);
 registerWrite(3, OFF, RED | BLUE | GREEN, TOP);
 registerWrite(4, OFF, RED | BLUE | GREEN, BOT);
 registerWrite(5, OFF, RED | BLUE | GREEN, BOT);
 registerWrite(6, OFF, RED | BLUE | GREEN, BOT);
 registerWrite(7, OFF, RED | BLUE | GREEN, BOT);
 registerWrite(8, OFF, RED | BLUE | GREEN, BOT);
 registerWrite(9, OFF, RED | BLUE | GREEN, BOT);
}

void flash(int color){
 registerWrite(1, ON, color, BOT);
 registerWrite(2, ON, color, MID);
 registerWrite(3, ON, color, TOP);
 registerWrite(4, ON, color, BOT);
 registerWrite(5, ON, color, BOT);
 registerWrite(6, ON, color, BOT);
 registerWrite(7, ON, color, BOT);
 registerWrite(8, ON, color, BOT);
 registerWrite(9, ON, color, BOT);
 
 delay(200);
 allOff();
 
 
}

void flashAll(){
 registerWrite(1, ON, RED, BOT);
 registerWrite(2, ON, RED, MID);
 registerWrite(3, ON, RED, TOP);
 registerWrite(4, ON, BLUE, BOT);
 registerWrite(5, ON, BLUE, MID);
 registerWrite(6, ON, BLUE, TOP);
 registerWrite(7, ON, GREEN, BOT);
 registerWrite(8, ON, GREEN, MID);
 registerWrite(9, ON, GREEN, TOP);
 
 delay(200);
 allOff();
 
 
}

void multiColorUpDown(int t, int loopt){
  int static x = 1;
  int static y = 0;
  int stopCount = 0;
  while(stopCount < loopt){//t * 50 (if t=100 then 15 SECONDS)
    if(x==10) {
      y++;
      x=1;
    }
    if(y%3==0){
      registerWrite(x, ON, RED, BOT);
      delay(t);
      registerWrite(x, OFF, RED, BOT);
    }
    else if(y%3==1){
      registerWrite(x, ON, GREEN, MID);
      delay(t);
      registerWrite(x, OFF, GREEN, MID);
    }
    else if(y%3==2){
      registerWrite(x, ON, BLUE, TOP);
      delay(t);
      registerWrite(x, OFF, BLUE, TOP);
    }

    x++;
    stopCount++;
  }
}

void multiColorUpDownR(int t, int loopt){
  int static x = 10;
  int static y = 0;
  int stopCount = 0;
  while(stopCount < loopt){//t * 50 (if t=100 then 15 SECONDS)
    if(x==0) {
      y++;
      x=10;
    }
    if(y%3==0){
      registerWrite(x, ON, RED, TOP);
      delay(t);
      registerWrite(x, OFF, RED, TOP);
    }
    else if(y%3==1){
      registerWrite(x, ON, GREEN, MID);
      delay(t);
      registerWrite(x, OFF, GREEN, MID);
    }
    else if(y%3==2){
      registerWrite(x, ON, BLUE, BOT);
      delay(t);
      registerWrite(x, OFF, BLUE, BOT);
    }
    y++;
    x--;
    stopCount++;
  }
}

void bouncing(int t, int color1, int color2){

  int loc = 1;
  int stopCount = 0;
  while(stopCount < 4){ //will run for 8t*50 (if t=75 then 15 secs)

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
    registerWrite(loc+3, OFF, color1, BOT);
    registerWrite(loc+3, OFF, color1, MID);
    registerWrite(loc+3, OFF, color1, TOP);
    stopCount++;
  }
}

void cross(int t){
  registerWrite(5, ON, RED | BLUE, MID);
  delay(1000);
  registerWrite(2, ON, RED, MID);
  registerWrite(8, ON, RED, MID);
  delay(1000);
  registerWrite(4, ON, RED, MID);
  registerWrite(6, ON, RED, MID);
  delay(1000);
  registerWrite(5, OFF, GREEN | BLUE, MID);
  registerWrite(2, OFF, RED, MID);
  registerWrite(8, OFF, RED, MID);
  registerWrite(4, OFF, RED, MID);
  registerWrite(6, OFF, RED, MID);
}

void growCube(int RED, int t, int corner, int pos){
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


  registerWrite(corner, ON, RED, pos);
  delay(t);
  registerWrite(f1, ON, RED, MID);
  registerWrite(f2, ON, RED, MID);
  registerWrite(5, ON, RED, MID);
  delay(t);
  registerWrite(s1, ON, RED, opp);
  registerWrite(s2, ON, RED, opp);
  registerWrite(s3, ON, RED, opp);
  registerWrite(s4, ON, RED, opp);
  registerWrite(s5, ON, RED, opp);
  delay(t);
  registerWrite(1, OFF, RED, BOT);
  registerWrite(2, OFF, RED, MID);
  registerWrite(4, OFF, RED, MID);
  registerWrite(5, OFF, RED, MID);
  registerWrite(3, OFF, RED, TOP);
  registerWrite(6, OFF, RED, TOP);
  registerWrite(7, OFF, RED, TOP);
  registerWrite(8, OFF, RED, TOP);
  registerWrite(9, OFF, RED, TOP);
}

void RotatingMerica(int t, int looptime){
  int stopCount = 0;
  while(stopCount < looptime){ //will run for t*50 (if t=300 then 15 secs)
    static int x = 1;
    if(x==1){
      registerWrite(5, ON, GREEN | BLUE  | RED, MID);
      registerWrite(2, ON, BLUE, MID);
      registerWrite(8, ON, BLUE, MID);
      registerWrite(4, ON, RED, MID);
      registerWrite(6, ON, RED, MID);
      delay(t);
      registerWrite(5, OFF, GREEN | BLUE | RED, MID);
      registerWrite(2, OFF, BLUE, MID);
      registerWrite(8, OFF, BLUE, MID);
      registerWrite(4, OFF, RED, MID);
      registerWrite(6, OFF, RED, MID);
      //delay(t);
      x++;
    }
    else if(x==2){
      registerWrite(5, ON, GREEN | BLUE | RED, BOT);
      registerWrite(1, ON, RED, BOT);
      registerWrite(7, ON, BLUE, BOT);
      registerWrite(3, ON, BLUE, BOT);
      registerWrite(9, ON, RED, BOT);
      delay(t);
      registerWrite(5, OFF, GREEN | BLUE | RED, BOT);
      registerWrite(1, OFF, RED, BOT);
      registerWrite(7, OFF, BLUE, BOT);
      registerWrite(3, OFF, BLUE, BOT);
      registerWrite(9, OFF, RED, BOT);
      //delay(t);
      x++;
    }
    else{
      registerWrite(5, ON, GREEN | BLUE | RED, TOP);
      registerWrite(1, ON, BLUE, TOP);
      registerWrite(7, ON, RED, TOP);
      registerWrite(3, ON, RED, TOP);
      registerWrite(9, ON, BLUE, TOP);
      delay(t);
      registerWrite(5, OFF, GREEN | BLUE | RED, TOP);
      registerWrite(5, OFF, GREEN, TOP);
      registerWrite(1, OFF, BLUE, TOP);
      registerWrite(7, OFF, RED, TOP);
      registerWrite(3, OFF, RED, TOP);
      registerWrite(9, OFF, BLUE, TOP);
      x=1;
      //delay(t);
    }
    stopCount++;
  }
}

void RotatingMerica2(int t){  // NOT WORKING & DON'T KNOW WHY!!!!!

  int stopCount = 0;
  while(stopCount < 50){ //will run for t*50 (if t=300 then 15 secs)
    static int x=1;//keeps track of level
    static int yy=3; //keeps track of rotation... trust me
    int y = yy%3;

    //t = (120/134)*1000;

    if(x==1){//middle
      if(y==0){
        registerWrite(5, ON, GREEN | BLUE, MID);
        registerWrite(2, ON, BLUE, MID);
        registerWrite(8, ON, BLUE, MID);
        registerWrite(4, ON, RED, MID);
        registerWrite(6, ON, RED, MID);
        delay(t);
        registerWrite(5, OFF, GREEN | BLUE, MID);
        registerWrite(2, OFF, BLUE, MID);
        registerWrite(8, OFF, BLUE, MID);
        registerWrite(4, OFF, RED, MID);
        registerWrite(6, OFF, RED, MID);
        //delay(t);
      }
      else if(y==1){//SECOND GO ROUND
        registerWrite(5, ON, GREEN | BLUE, MID);
        registerWrite(1, ON, BLUE, MID);
        registerWrite(9, ON, BLUE, MID);
        registerWrite(3, ON, RED, MID);
        registerWrite(7, ON, RED, MID);
        delay(t);
        registerWrite(5, OFF, GREEN | BLUE, MID);
        registerWrite(1, OFF, BLUE, MID);
        registerWrite(9, OFF, BLUE, MID);
        registerWrite(3, OFF, RED, MID);
        registerWrite(7, OFF, RED, MID);
      }
      else{//THIRD GO ROUND
        registerWrite(5, ON, GREEN | BLUE, MID);
        registerWrite(2, ON, RED, MID);
        registerWrite(8, ON, RED, MID);
        registerWrite(4, ON, BLUE, MID);
        registerWrite(6, ON, BLUE, MID);
        delay(t);
        registerWrite(5, OFF, GREEN | BLUE, MID);
        registerWrite(2, OFF, RED, MID);
        registerWrite(8, OFF, RED, MID);
        registerWrite(4, OFF, BLUE, MID);
        registerWrite(6, OFF, BLUE, MID);
      }
      x++;
    }
    else if(x==2){//BOTTOM
      if(y==0){
        registerWrite(5, ON, GREEN | BLUE | RED, BOT);
        registerWrite(1, ON, RED, BOT);
        registerWrite(7, ON, BLUE, BOT);
        registerWrite(3, ON, BLUE, BOT);
        registerWrite(9, ON, RED, BOT);
        delay(t);
        registerWrite(5, OFF, GREEN, BOT);
        registerWrite(5, OFF, BLUE, BOT);
        registerWrite(1, OFF, RED, BOT);
        registerWrite(7, OFF, BLUE, BOT);
        registerWrite(3, OFF, BLUE, BOT);
        registerWrite(9, OFF, RED, BOT);
        //delay(t);
      }
      else if(y==1){
        registerWrite(5, ON, GREEN | BLUE | RED, BOT);
        registerWrite(4, ON, RED, BOT);
        registerWrite(6, ON, RED, BOT);
        registerWrite(2, ON, BLUE, BOT);
        registerWrite(8, ON, BLUE, BOT);
        delay(t);
        registerWrite(5, OFF, GREEN | BLUE | RED, BOT);
        registerWrite(4, OFF, RED, BOT);
        registerWrite(6, OFF, RED, BOT);
        registerWrite(2, OFF, BLUE, BOT);
        registerWrite(8, OFF, BLUE, BOT);
        //delay(t);
      }
      else{
        registerWrite(5, ON, GREEN | BLUE | RED, BOT);
        registerWrite(3, ON, RED, BOT);
        registerWrite(7, ON, RED, BOT);
        registerWrite(1, ON, BLUE, BOT);
        registerWrite(9, ON, BLUE, BOT);
        delay(t);
        registerWrite(5, OFF, GREEN | BLUE | RED, BOT);
        registerWrite(3, OFF, RED, BOT);
        registerWrite(7, OFF, RED, BOT);
        registerWrite(1, OFF, BLUE, BOT);
        registerWrite(9, OFF, BLUE, BOT);
        //delay(t);
      }
      x++;
    }
    else{
      if(y==0){
        registerWrite(5, ON, BLUE, TOP);
        registerWrite(5, ON, GREEN, TOP);
        registerWrite(1, ON, BLUE, TOP);
        registerWrite(7, ON, RED, TOP);
        registerWrite(3, ON, RED, TOP);
        registerWrite(9, ON, BLUE, TOP);
        delay(t);
        registerWrite(5, OFF, BLUE, TOP);
        registerWrite(5, OFF, GREEN, TOP);
        registerWrite(1, OFF, BLUE, TOP);
        registerWrite(7, OFF, RED, TOP);
        registerWrite(3, OFF, RED, TOP);
        registerWrite(9, OFF, BLUE, TOP);
        //delay(t);
      }
      else if(y==1){
        registerWrite(5, ON, BLUE | GREEN | RED, TOP);
        registerWrite(4, ON, BLUE, TOP);
        registerWrite(2, ON, RED, TOP);
        registerWrite(8, ON, RED, TOP);
        registerWrite(6, ON, BLUE, TOP);
        delay(t);
        registerWrite(5, OFF, BLUE | GREEN | RED, TOP);
        registerWrite(4, OFF, BLUE, TOP);
        registerWrite(2, OFF, RED, TOP);
        registerWrite(8, OFF, RED, TOP);
        registerWrite(6, OFF, BLUE, TOP);
        //delay(t);
      }
      else{
        registerWrite(5, ON, BLUE | GREEN | RED, TOP);
        registerWrite(1, ON, BLUE, TOP);
        registerWrite(3, ON, RED, TOP);
        registerWrite(7, ON, RED, TOP);
        registerWrite(9, ON, BLUE, TOP);
        delay(t);
        registerWrite(5, OFF, BLUE | GREEN | RED, TOP);
        registerWrite(1, OFF, BLUE, TOP);
        registerWrite(3, OFF, RED, TOP);
        registerWrite(7, OFF, RED, TOP);
        registerWrite(9, OFF, BLUE, TOP);
      }
      x=1;
    }
    //delay();
    yy++;
    stopCount++;
  }
}

// Cube arrangment with location of LED if look upon from above and the shift registers were to the left
//  9 | 8 | 7
//  6 | 5 | 4
//  3 | 2 | 1


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
  if(state == ON){ 
    digitalWrite(row, ON);
  }
  else{ 
    digitalWrite(row, OFF); 
  }
}





