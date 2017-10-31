#include <Wire.h>

int segA = 2;
int segB = 3;
int segC = 4;
int segD = 5;
int segE = 6;
int segF = 7;
int segG = 8;
int segDP = 9;
int button1 = 10;
int ledButton1 = 11;
int button2 = 12;
int ledButton2 = 13;
int led = 14;
int sensor = 16;
int button1State = 0;
int button2State = 0;
int button1SetupState = 0;
int button2SetupState = 0;
int button1LastState = 0;
int button2LastState = 0;
int sensorState = 0;
int sensorLastState = 0;
int doorState = 0;
int verdieping;
int verdiepingNieuw;
int eigenVerdieping;

#define on  HIGH
#define off  LOW

void setup() {
  Serial.begin (9600);
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(segDP, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(ledButton1, OUTPUT);
  pinMode(button2, INPUT);
  pinMode(ledButton2, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(sensor, INPUT_PULLUP);

  digitalWrite(led, on);
  digitalWrite(ledButton1, on);
  digitalWrite(ledButton2, on);
  int count = 0;
  while (button2SetupState == off) {
    button1SetupState = digitalRead(button1);
    button2SetupState = digitalRead(button2);
    if (button1SetupState != button1LastState) {
      if (button1SetupState == on) {
        count++;
        if (count > 9)
          count = 0;
      }
    }
    showNumber(count);
    eigenVerdieping = count;
    verdieping = eigenVerdieping;
    verdiepingNieuw = eigenVerdieping;
    button1LastState = button1SetupState;
  }
  delay(1000);
  digitalWrite(led, off);
  digitalWrite(ledButton1, off);
  digitalWrite(ledButton2, off);

  Wire.begin(eigenVerdieping + 8);
  Wire.onReceive(getLiftRelatedData);
  Wire.onRequest(sendDataToMaster);
}

void getLiftRelatedData() {
  verdieping = Wire.read();
  verdiepingNieuw = Wire.read();
}

void sendDataToMaster() {
  Wire.write(sensorState);
  Wire.write(doorState);
  Wire.write(button1State);
  Wire.write(button2State);
}

void getal0()
{
  digitalWrite(segA, on);
  digitalWrite(segB, on);
  digitalWrite(segC, on);
  digitalWrite(segD, on);
  digitalWrite(segE, on);
  digitalWrite(segF, on);
  digitalWrite(segG, off);
  digitalWrite(segDP, off);
}

void getal1()
{
  digitalWrite(segA, off);
  digitalWrite(segB, on);
  digitalWrite(segC, on);
  digitalWrite(segD, off);
  digitalWrite(segE, off);
  digitalWrite(segF, off);
  digitalWrite(segG, off);
  digitalWrite(segDP, off);
}
void getal2()
{
  digitalWrite(segA, on);
  digitalWrite(segB, on);
  digitalWrite(segC, off);
  digitalWrite(segD, on);
  digitalWrite(segE, on);
  digitalWrite(segF, off);
  digitalWrite(segG, on);
  digitalWrite(segDP, off);
}

void getal3()
{
  digitalWrite(segA, on);
  digitalWrite(segB, on);
  digitalWrite(segC, on);
  digitalWrite(segD, on);
  digitalWrite(segE, off);
  digitalWrite(segF, off);
  digitalWrite(segG, on);
  digitalWrite(segDP, off);
}

void getal4()
{
  digitalWrite(segA, off);
  digitalWrite(segB, on);
  digitalWrite(segC, on);
  digitalWrite(segD, off);
  digitalWrite(segE, off);
  digitalWrite(segF, on);
  digitalWrite(segG, on);
  digitalWrite(segDP, off);
}

void getal5()
{
  digitalWrite(segA, on);
  digitalWrite(segB, off);
  digitalWrite(segC, on);
  digitalWrite(segD, on);
  digitalWrite(segE, off);
  digitalWrite(segF, on);
  digitalWrite(segG, on);
  digitalWrite(segDP, off);
}

void getal6()
{
  digitalWrite(segA, on);
  digitalWrite(segB, off);
  digitalWrite(segC, on);
  digitalWrite(segD, on);
  digitalWrite(segE, on);
  digitalWrite(segF, on);
  digitalWrite(segG, on);
  digitalWrite(segDP, on);
}

void getal7()
{
  digitalWrite(segA, on);
  digitalWrite(segB, on);
  digitalWrite(segC, on);
  digitalWrite(segD, off);
  digitalWrite(segE, off);
  digitalWrite(segF, off);
  digitalWrite(segG, off);
  digitalWrite(segDP, off);
}

void getal8()
{
  digitalWrite(segA, on);
  digitalWrite(segB, on);
  digitalWrite(segC, on);
  digitalWrite(segD, on);
  digitalWrite(segE, on);
  digitalWrite(segF, on);
  digitalWrite(segG, on);
  digitalWrite(segDP, off);
}

void getal9()
{
  digitalWrite(segA, on);
  digitalWrite(segB, on);
  digitalWrite(segC, on);
  digitalWrite(segD, on);
  digitalWrite(segE, off);
  digitalWrite(segF, on);
  digitalWrite(segG, on);
  digitalWrite(segDP, on);
}

void showNumber(int getal)
{
  switch (getal) {
    case 0:
      getal0();
      break;
    case 1:
      getal1();
      break;
    case 2:
      getal2();
      break;
    case 3:
      getal3();
      break;
    case 4:
      getal4();
      break;
    case 5:
      getal5();
      break;
    case 6:
      getal6();
      break;
    case 7:
      getal7();
      break;
    case 8:
      getal8();
      break;
    case 9:
      getal9();
      break;
  }
}


void loop() {

  sensorState = !digitalRead(sensor);

  if (digitalRead(button1) != button1LastState) {
    if (digitalRead(button1) == on) {
      button1State = 1;
      digitalWrite(ledButton1, on);
      verdiepingNieuw = eigenVerdieping;
    }
    delay(50);
  }
  if (digitalRead(button2) != button2LastState) {
    if (digitalRead(button2) == on) {
      button2State = 1;
      digitalWrite(ledButton2, on);
      verdiepingNieuw = eigenVerdieping;
    }
    delay(50);
  }

  if(sensorState && verdiepingNieuw == eigenVerdieping && verdieping == eigenVerdieping){
    Serial.println("verdieping is er");
    digitalWrite(ledButton2, off);
    digitalWrite(ledButton1, off);
    showNumber(eigenVerdieping);
    doorState = 1;
    Serial.println(doorState);
    button1State = 0;
    button2State = 0;
    delay(1000);
    digitalWrite(led, on);
    delay(4000);
    digitalWrite(led, off);
    doorState = 0;
    Serial.println(doorState);
  }
   
  showNumber(verdieping);
}
