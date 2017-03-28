#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"   

int tm = 0;

const int fanPin=33;
const int BlueLED = 14;
const int RedLED = 15;
const int Flame1Pin = 14;
const int Flame2Pin = 15;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);

int dist1, dist2, dist3;

void setup() {
  pinMode(fanPin,OUTPUT);
  pinMode(BlueLED,OUTPUT);
  pinMode(RedLED,OUTPUT);

  Serial.begin(9600);
  AFMS.begin();
  myMotor1->setSpeed(200);
  myMotor2->setSpeed(200);
  myMotor3->setSpeed(200);
  myMotor4->setSpeed(200);

 


}

void Stop()
{
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
  myMotor3->run(RELEASE);
 
}

void fanOn()
{
    digitalWrite(fanPin,HIGH);
}

void fanOff()
{
  digitalWrite(fanPin,LOW);
}

void BlueLEDOn()
{
  digitalWrite(BlueLED,HIGH);
}

void BlueLEDOff()
{
  digitalWrite(BlueLED, LOW);
}

void RedLEDON()
{
  digitalWrite(RedLED,HIGH);
}

void RedLEDOff()
{
 digitalWrite(RedLED,LOW); 
}

int Flame1()
{ 
  int x,total;
  for(int i = 0; i < 15;i++)
  {
  x = analogRead(Flame1Pin);
  total = total + x;
    //delay(20);
  }
  total = total/15;

  return total;
}

int Flame2()
{ 
  int x,total;
  for(int i = 0; i < 15;i++)
  {
  x = analogRead(Flame2Pin);
  total = total + x;
    //delay(20);
  }
  total = total/15;

  return total;
}

int sensor1()
{
  int total = 0;
    int x, y;
  for(int i = 0; i < 10;i++)
  {

  x = analogRead(10);
  y = 3163.6*pow(x,-1.052);
  total = total + y;
  //Serial.println(y);
  }
  total = total/10;
  return total;
}

int sensor2()
{
  int x, y;
  x = analogRead(11);
  y = 1770.6*pow(x,-0.943);
 // Serial.println(y);
  return y;
}


int sensor3()
{ 
  int total = 0;
  int x, y;
  for(int i = 0; i < 10;i++)
  {
 
  x = analogRead(12);
  y = 1770.6*pow(x,-0.943);
  total = total + y;
  //Serial.println(y);
  delay(3);
  
  }
  total = total/10;
  return total;
}

void forward()
{
    myMotor1->setSpeed(200);
  myMotor2->setSpeed(200);
  myMotor3->setSpeed(200);
  myMotor1->run(FORWARD);
  myMotor2->run(FORWARD);
  myMotor3->run(RELEASE);
}

void left()
{

}

void right()
{

}

void rotateCW()
{
  myMotor1->setSpeed(100);
  myMotor2->setSpeed(100);
  myMotor3->setSpeed(100);
  myMotor1->run(BACKWARD);
  myMotor2->run(FORWARD);
  myMotor3->run(BACKWARD);
  
}

void rotateCCW()
{
    for(int i = 0; i < 100;i++)
  {
  myMotor1->setSpeed(100);
  myMotor2->setSpeed(100);
  myMotor3->setSpeed(100);
  myMotor1->run(FORWARD);
  myMotor2->run(BACKWARD);
  myMotor3->run(FORWARD);
  }
}

void rotateCCWCont()
{

  myMotor1->setSpeed(100);
  myMotor2->setSpeed(100);
  myMotor3->setSpeed(100);
  myMotor1->run(FORWARD);
  myMotor2->run(BACKWARD);
  myMotor3->run(FORWARD);
 
}

void oneRotationCW()
{ 
  for(int i = 0; i < 400; i++)
  {
    //FlameCheck();
    myMotor1->setSpeed(100);
    myMotor2->setSpeed(100);
    myMotor3->setSpeed(100);
    myMotor1->run(BACKWARD);
    myMotor2->run(FORWARD);
    myMotor3->run(BACKWARD);
  }
}

void veerLeft()
{ 
  myMotor1->setSpeed(200);
  myMotor3->setSpeed(200);
  myMotor2->setSpeed(150);
  myMotor1->run(FORWARD);
  myMotor2->run(FORWARD);
  myMotor3->run(RELEASE);
}

void veerRight()
{
  myMotor2->setSpeed(200);
  myMotor3->setSpeed(200);
  myMotor1->setSpeed(150);
  myMotor1->run(FORWARD);
  myMotor2->run(FORWARD);
  myMotor3->run(RELEASE);
}

void FlameCheck()
{

  int f1,f2, total, dif;
  f1 = Flame1();
  f2 = Flame2();
  dif = f2-f1;
  

  total = f1 + f2;

  if(total > 150)
  {
    Stop();
    fanOn();
    delay(2000);
    fanOff();
    
  }
  /*else if(f1 > f2 && total > 150)
  {
    rotateCW();
  }
  else if(f2 > f1 && total > 150)
  {
    rotateCCWCont();
  }*/

    
  
}

void ArcRight()
{
  myMotor2->setSpeed(200);
  myMotor3->setSpeed(0);
  myMotor1->setSpeed(50);
  myMotor1->run(FORWARD);
  myMotor2->run(FORWARD);
  myMotor3->run(RELEASE);
}


 
void loop() {

  tm++;
  Serial.println(tm);;
  if(tm == 10)
  {
    delay(1000);
    Serial.println("Nigger");
    oneRotationCW();
    RedLEDON();
    tm = 0;
  }

  FlameCheck();

  dist1 = sensor1();
 
  dist2 = sensor3();
  //Serial.println(dist2);

  if(dist2 > 20)
    {

    if(dist1 < 6)
    {
      rotateCCWCont();
    }
    
    else if( dist1 > 20&& dist1 < 30)
     veerRight();
  
    else if( dist1 > 30)
    {
      forward();
      delay(300);
      while( dist1 > 30)
      {
      ArcRight();
      dist1 = sensor1();
      }
    }
     else
      veerLeft();
    //else if( dist3 >
  
    //rotateCW();
  }


  else if(dist2 < 20)
  {
    //Stop();
    //delay(5000);
    rotateCCW();
  }
  
  

  
  
}
