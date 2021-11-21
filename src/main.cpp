#include <Arduino.h>
#include "Lighting.hpp"
#include "DynamicEffects.hpp"
#include "StaticEffects.hpp"
#include "Timing.hpp"
/*
*
Warning!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Don not forget to call ResetMbrVars() in between Dynamic animation method calls
*
*/

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
/*
*
Warning!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Don not forget to call ResetMbrVars() in between Dynamic animation method calls
*
*/


  // put your main code here, to run repeatedly:
  //Leds.BusyPattern();
  //StaticPicture.ChristmasOriginal(Colors::fullcolor,Colors::fullbrightness);
  //DynamicAnimation.ChristmasOriginalBreathing(15,Colors::fullbrightness);
    DynamicAnimation.ChristmasOriginalTwinkling(30,10,Colors::fullcolor,Colors::fullbrightness);
  //DynamicAnimation.ColorCycle(20);
  //DynamicAnimation.BreathingColorCycle(5,5,191,Colors::fullbrightness);

   // DynamicAnimation.RandomColorsAllFading(25, Colors::fullcolor, Colors::halfbrightness-35);
   //DynamicAnimation.RandomAllValsFade(20);

  //DynamicAnimation.RandomColor(1*TO_SECONDS,255,255);
  //DynamicAnimation.RandomColorCycle(30, Colors::fullcolor, Colors::fullbrightness);
  //DynamicAnimation.RandomColorsAll(100,Colors::fullcolor,Colors::fullbrightness);


  //DynamicAnimation.CycleColorList(Colors::fullcolor,Colors::fullbrightness,2000,5,Colors::orangeRed,Colors::aqua,Colors::pink,Colors::green,Colors::yellow);
  //DynamicAnimation.CycleColorList(Colors::fullcolor,Colors::fullbrightness,2000,5,Colors::orange,Colors::white,Colors::purple,Colors::blue,Colors::red);
}