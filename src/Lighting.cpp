#include "Lighting.hpp"


///////////////////////////
FASTLED_USING_NAMESPACE
#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define RightStrandPin   14 //used to be 5 for silk screen mapping, now 14 for esp8266 chip pin mapping idk what changed
#define LeftStrandPin    12//used to be 6 for silk screen mapping, now 12 for esp8266 chip pin mapping idk what changed
//#define CLK_PIN   4      //don't know what this would change to like above, never needed for this chipset
#define NUM_LEDS 60
CRGB RightStrand[NUM_LEDS];
CRGB LeftStrand[NUM_LEDS];
#define CHIPSET_TYPE WS2811
#define COLOR_ORDER RGB
#define BRIGHTNESS         127//96 was the original value
#define FRAMES_PER_SECOND  120
//////////////////////////




Lighting::Lighting()
{

}

Lighting::~Lighting()
{

}

void Lighting::InitFastLED()
{
	FastLED.addLeds<CHIPSET_TYPE, RightStrandPin, COLOR_ORDER>(RightStrand, NUM_LEDS).setCorrection(TypicalLEDStrip);
	FastLED.addLeds<CHIPSET_TYPE, LeftStrandPin, COLOR_ORDER>(LeftStrand, NUM_LEDS).setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(BRIGHTNESS);
}

void Lighting::TestStrands()
{
	for(int i = 0; i < NUM_LEDS; i++)
	{
	RightStrand[0] = CRGB::Red;
	LeftStrand[0] = CRGB::Green;
	FastLED.show();
	}
	delay(3000);
	for(int i = 0; i < NUM_LEDS; i++)
	{
	RightStrand[0] = CRGB::Black;
	LeftStrand[0] = CRGB::Black;
	FastLED.show();
	}
}