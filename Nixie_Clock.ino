#include <virtuabotixRTC.h>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Global Variables>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
const int clk = 5; //Clock pin of DS1302
const int dat = 6; //Data(I/O) pin of DS1302
const int rst = 7; //Reset(CE) pin of DS1302
virtuabotixRTC DS1302(clk, dat, rst); //initialize the DS1302 using the virtuaboticRTC library (DS1302 is variable)

int latchPin = 9; //latch pin for both shift registers
int clockPin = 10; //clock pin for both shift registers
int dataPin = 8; //data pin of first shift register

//byte that will hold the final byte to be sent to shift registers for hours
byte minutesOutput;
byte hoursOutput;

//constant byte arrays that hold the properly formated data to be sent to shift registers. Number in array aligns with digits ie 1=1
const byte minuTens[6] = {0b00000000,0b10000000,0b01000000,0b11000000,0b00100000,0b10100000};
const byte minuOnes[10] = {0b00000000,0b00001000,0b00000100,0b00001100,0b00000010,0b00001010,0b00000110,0b00001110,0b00000001,0b00001001};
const byte hourTens[3] = {0b00000000,0b10000000,0b01000000};
const byte hourOnes[10] = {0b00000000,0b00001000,0b00000100,0b00001100,0b00000010,0b00001010,0b00000110,0b00001110,0b00000001,0b00001001};

//string to hold the separated digits
String minuTensHolder;
String minuOnesHolder;
String hourTensHolder;
String hourOnesHolder;

//int that will pull the hours and minutes out of the DS1302
int minutes;
int hours;

//string used to separate the digits in minutes and hours
String mins;
String hrs;

//ints to hold single digits to be used to determine which byte to use in the arrays.
int a;
int b;
int c;
int d;
const String leadingZero = "0";
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<End Global Variables>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/*Setup is initializing which pins will be used for what purpose.
  This happens before the program run as the arduino is being
  started, and only then.*/
void setup() 
{
  //Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  //DS1302.setDS1302Time(00, 58, 23, 3, 10, 5, 2016);
}

//this is the program itself. This is where everything happens.
void loop() 
{
  DS1302.updateTime(); //have the DS1302 update the time
  minutes = DS1302.minutes; //pull minutes out of DS1302
  hours = DS1302.hours; //pull hours out of DS1302
  if (minutes<10)
  {
    mins = String(leadingZero + minutes); //this adds a leading zero onto the string and assigns it to temp holder
  }
  else
  {
    mins = String(minutes); //assigns it to temp holder
  }

  if (hours<10)
  {
    hrs = String(leadingZero + hours); //this adds a leading zero onto the string and assigns it to temp holder
  }
  else
  {
    hrs = String(hours); //assigns it to temp holder
  }

  minuTensHolder = mins[0]; //draw first digit out of string
  minuOnesHolder = mins[1]; //draw second digit out of string
  hourTensHolder = hos[0]; //draw first digt out of string
  hourOnesHolder = hos[1]; //draw second digit out of string
  
  //assign back to int
  c = minuTensHolder.toInt();
  d = minuOnesHolder.toInt();
  a = hourTensHolder.toInt();
  b = hourOnesHolder.toInt();
  
  //assemble
  minutesOutput = minuTens[c] + minuOnes[d];
  hoursOutput = hourTens[a] + hourOnes[b];
  
  //send to shift registers
  updateRegister(minutesOutput, hoursOutput);

//  delay(200);
//  minutes = minutes + 1;
//  hours = hours + 1; 
//  if (minutes > 59)
//  {
//    minutes = 0;
//  }
//  if (hours > 23)
//  {
//    hours = 0;
//  }
//  Serial.print(a);
//  Serial.print(b);
//  Serial.println("");
//  Serial.print(c);
//  Serial.print(d);
//  delay(200);
//  Serial.println("");
//  Serial.print(DS1302.hours);
//  Serial.print(":");
//  Serial.print(DS1302.minutes);
//  Serial.println("");
  
}

void updateRegister(byte input1, byte input2)
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, input2);
  shiftOut(dataPin, clockPin, LSBFIRST, input1);
  digitalWrite(latchPin, HIGH);
}
