#include <Arduino.h>
#include "Lighting.hpp"
#include "DynamicEffects.hpp"
#include "StaticEffects.hpp"
#include "Timing.hpp"


Lighting Leds;
DynamicEffects DynamicAnimation;
StaticEffects StaticPicture;

Timing BaseTimer;

void setup() {
  // put your setup code here, to run once:
  delay(3000);//allow 3s for recovery
  Serial.begin(9600);
  Leds.TestStrands();
  delay(1000);//set small delay again before program starts - May want to remove depending on program requirements
}

void loop() {
  // put your main code here, to run repeatedly:
  //Leds.BusyPattern();
  //DynamicAnimation.ColorCycle(20);
  DynamicAnimation.BreathingColorCycle(5,5,191,Colors::fullbrightness);

    
  //DynamicAnimation.CycleColorList(Colors::fullcolor,Colors::fullbrightness,2000,5,Colors::orangeRed,Colors::aqua,Colors::pink,Colors::green,Colors::yellow);
  //DynamicAnimation.CycleColorList(Colors::fullcolor,Colors::fullbrightness,2000,5,Colors::orange,Colors::white,Colors::purple,Colors::blue,Colors::red);
  /*
  StaticPicture.USARedWhiteBlue();
  delay(1000);
  StaticPicture.PeppermintRWG();
  delay(1000);
  StaticPicture.PeppermintRW();
  delay(1000);
  StaticPicture.PeppermintRG();
  delay(1000);
  StaticPicture.PeppermintGW();
  delay(1000);
  StaticPicture.ShowColor(Colors::yellow);
  delay(1000);
  StaticPicture.ShowTwoColors(Colors::purple,Colors::aqua);
  delay(1000);*/
  
}