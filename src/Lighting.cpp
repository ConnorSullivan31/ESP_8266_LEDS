#include "Lighting.hpp"


///////////////////////////FastLED Defines
FASTLED_USING_NAMESPACE
#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif
/////////
#define RightStrandPin   14 //used to be 5 for silk screen mapping, now 14 for esp8266 chip pin mapping idk what changed
#define LeftStrandPin    12//used to be 6 for silk screen mapping, now 12 for esp8266 chip pin mapping idk what changed

#define NUM_STRANDS 2 //Defined from Right to Left
#define NUM_LEDS 50

#define CHIPSET_TYPE WS2811
#define COLOR_ORDER RGB

#define BRIGHTNESS         255//96 was the original value
#define FRAMES_PER_SECOND  120//Maybe I'll use this one day
//////////////////////////
CRGB LedStrandArray[NUM_STRANDS][NUM_LEDS];//Order is Right to Left
//////////////////////////


namespace Colors
{
int red=0;
int orangeRed=24;
int orange=32;
int yellow=64;
int green=96;
int aqua=128;
int blue=160;
int purple=192;
int pink=224;
int fullcolor=255;
int halfcolor=127;
int white=0;
int quarterbrightness=63;
int halfbrightness=127;
int fullbrightness=255;
int black=0;
}


Lighting::Lighting()
{
ResetToBlack();
InitFastLED();
}

Lighting::~Lighting()
{

}

void Lighting::InitFastLED()
{
	FastLED.addLeds<CHIPSET_TYPE, RightStrandPin, COLOR_ORDER>(LedStrandArray[0], NUM_LEDS).setCorrection(TypicalLEDStrip);
	FastLED.addLeds<CHIPSET_TYPE, LeftStrandPin, COLOR_ORDER>(LedStrandArray[1], NUM_LEDS).setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(BRIGHTNESS);
}

void Lighting::ResetToBlack(bool show_reset)
{
	for(int i = 0; i < NUM_LEDS; i++)//Set LEDs to black
	{
	LedStrandArray[0][i] = CRGB::Black;
	LedStrandArray[1][i] = CRGB::Black;
	}
	if(show_reset)
	{
		FastLED.show();
	}
}

void Lighting::TestStrands()
{
	using namespace Colors;

	ResetToBlack();//Set Leds to black and make sure there are no stored colors
	delay(10);//give leds a breather b4 starting up

	for(int i = 0; i < NUM_LEDS; i++)//show all white and aqua as test
	{
	LedStrandArray[0][i].setHSV(white,white,fullbrightness);
	LedStrandArray[1][i].setHSV(aqua,fullcolor,fullbrightness);
	}
	FastLED.show();
	
	delay(3000);
	ResetToBlack();//Set leds back to black
}

void Lighting::BusyPattern()
{
	for(int hue = 0; hue<=255; hue++)
	{
		for(int i = 0; i < NUM_LEDS; i++)
		{
			LedStrandArray[0][i].setHSV(hue,255,255);
			LedStrandArray[1][i].setHSV(hue,255,255);
		}
		delay(30);
		FastLED.show();
	}
}