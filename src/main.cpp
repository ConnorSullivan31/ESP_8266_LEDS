#include <Arduino.h>
#include "Lighting.hpp"
#include "Timing.hpp"


const int led = 2, led2 = 16;


Lighting Leds;
Timing BaseTimer;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);
  Leds.TestStrands();
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(BaseTimer.GetProgramEpoch());
}