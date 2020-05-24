#include <SoftwareSerial.h>

SoftwareSerial BT(0, 1); //TX, RX respetively 
String voicein;
int c,n;
String voicein1;
const int m1a=6; // set motor pins
const int m1b=5;
const int m2a=10;
const int m2b=11;

void setup() {
  BT.begin(9600); 
  Serial.begin(9600);
  pinMode(m1a, OUTPUT); 
  pinMode(m1b, OUTPUT);
  pinMode(m2a, OUTPUT);
  pinMode(m2b, OUTPUT);
}


void on(int a, int b)
{
  analogWrite (a,150); // move the motor slowly
  analogWrite (b,150);
}

void off(int a, int b)
{
  digitalWrite(a,LOW); 
  digitalWrite(b,LOW);
}

void stop1()
{
   digitalWrite (m1a, LOW);
   digitalWrite (m1b, LOW); 
   digitalWrite (m2a, LOW);
   digitalWrite (m2b, LOW); 
}

void loop() { 
  while (BT.available()){ //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable  
  c = BT.read(); //Conduct a serial read
  if(isDigit(c)){
  voicein1 +=(char)c; //build the string- "forward", "reverse", "left" and "right" 
  } 
  else {
    voicein+=(char)c;
  }
  } 
  if (voicein.length() > 0) {
  Serial.println(voicein);
  n=voicein1.toInt();
  Serial.println(n);
  if(voicein == " forward")
      { 
        on(m1a,m2a);
        off(m1b,m2b); 
        delay(n*80);// to make the robot move forward for specified distance 
        stop1(); // stop the robot
        delay(100); 
      } 
   else if(voicein == " back") 
      { 
        on(m1b,m2b);
        off(m1a,m2a);
        delay(n*80);// to make the robot move back for specified distance 
        stop1(); // stop the robot
        delay(100); 
      } 
      else if (voicein == " left") 
      {
        on(m1a,m2b);
        off(m1b,m2a); //turn left and then move forward
        delay(1800);
        on(m1a,m2a);
        off(m1b,m2b); 
        delay(n*80);// to make the robot move left for specified distance 
        stop1(); // stop the robot
        delay(100); 
      } 
      else if ( voicein == " right")
      {
        on(m1b,m2a);
        off(m1a,m2b); //turn right and then move forward
        delay(1800);
        on(m1a,m2a);
        off(m1b,m2b); 
        delay(n*80);// to make the robot move right for specified distance 
        stop1(); // stop the robot
        delay(100); 
      }
      else if (voicein == "stop") 
      { 
        stop1();
        delay (100); 
      }
      else {
        stop1();
      }
      voicein="";//Reset the variable
      voicein1="";
      n=0;
      }
}
// app used for this project is developed by me through MIT app inventor 2
// By Tejaswini Holla K 
