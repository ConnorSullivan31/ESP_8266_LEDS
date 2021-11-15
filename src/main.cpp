#include <Arduino.h>
#include "Lighting.hpp"
#include "Timing.hpp"




Lighting Leds;
Timing BaseTimer;

void setup() {
  // put your setup code here, to run once:
  delay(3000);//allow 3s for recovery
  Serial.begin(9600);
  Leds.TestStrands();
}

void loop() {
  // put your main code here, to run repeatedly:
  Leds.BusyPattern();
}