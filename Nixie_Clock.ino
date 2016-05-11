#include <virtuabotixRTC.h>

const int clk = 5;
const int dat = 6;
const int rst = 7;
virtuabotixRTC myRTC(clk, dat, rst);

//ABCD for NIXIE Tubes
//0 = 0000
//1 = 1000
//2 = 0100
//3 = 1100
//4 = 0010
//5 = 1010
//6 = 0110
//7 = 1110
//8 = 0001
//9 = 1001

int latchPin = 9;
int clockPin = 10;
int dataPin = 8;
byte input1;
byte input2;
const byte minuTens[6] = {0b00000000,0b10000000,0b01000000,0b11000000,0b00100000,0b10100000};
const byte minuOnes[10] = {0b00000000,0b00001000,0b00000100,0b00001100,0b00000010,0b00001010,0b00000110,0b00001110,0b00000001,0b00001001};
const byte hourTens[3] = {0b00000000,0b10000000,0b01000000};
const byte hourOnes[10] = {0b00000000,0b00001000,0b00000100,0b00001100,0b00000010,0b00001010,0b00000110,0b00001110,0b00000001,0b00001001};
String minuTensHolder;
String minuOnesHolder;
String hourTensHolder;
String hourOnesHolder;
int minutes;
int hours;
String mins;
String hos;
int a;
int b;
int c;
int d;
const String leadingZero = "0";

void setup() 
{
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  //myRTC.setDS1302Time(00, 58, 23, 3, 10, 5, 2016);
}

void loop() 
{
  myRTC.updateTime();
  minutes = myRTC.minutes;
  hours = myRTC.hours;
  if (minutes<10)
  {
    mins = String(leadingZero + minutes);
  }
  else
  {
    mins = String(minutes);
  }

  if (hours<10)
  {
    hos = String(leadingZero + hours);
  }
  else
  {
    hos = String(hours);
  }

  minuTensHolder = mins[0];
  minuOnesHolder = mins[1];
  hourTensHolder = hos[0];
  hourOnesHolder = hos[1];
  c = minuTensHolder.toInt();
  d = minuOnesHolder.toInt();
  a = hourTensHolder.toInt();
  b = hourOnesHolder.toInt();
  
  input1 = minuTens[c] + minuOnes[d];
  input2 = hourTens[a] + hourOnes[b];
  updateRegister(input1, input2);

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
//  Serial.print(myRTC.hours);
//  Serial.print(":");
//  Serial.print(myRTC.minutes);
//  Serial.println("");
  
}

void updateRegister(byte input1, byte input2)
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, input2);
  shiftOut(dataPin, clockPin, LSBFIRST, input1);
  digitalWrite(latchPin, HIGH);
}
