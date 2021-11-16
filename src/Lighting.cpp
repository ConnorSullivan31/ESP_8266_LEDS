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
enum StrandOrder{RightStrand = 0, LeftStrand = 1, Strand3 = 2, Strand4 = 3};//Order the leds
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
m_num_leds = NUM_LEDS;
}

Lighting::~Lighting()
{

}

void Lighting::InitFastLED()
{
	FastLED.addLeds<CHIPSET_TYPE, RightStrandPin, COLOR_ORDER>(LedStrandArray[RightStrand], NUM_LEDS).setCorrection(TypicalLEDStrip);//Right Strand
	FastLED.addLeds<CHIPSET_TYPE, LeftStrandPin, COLOR_ORDER>(LedStrandArray[LeftStrand], NUM_LEDS).setCorrection(TypicalLEDStrip);//Left Strand
	FastLED.setBrightness(BRIGHTNESS);
}


//Basic Ops

void Lighting::ResetToBlack(bool show_reset)
{
	for(int i = 0; i < NUM_LEDS; i++)//Set LEDs to black
	{
	LedStrandArray[RightStrand][i] = CRGB::Black;
	LedStrandArray[LeftStrand][i] = CRGB::Black;
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
	LedStrandArray[RightStrand][i].setHSV(green,fullcolor,fullbrightness);//Right Strand
	LedStrandArray[LeftStrand][i].setHSV(aqua,fullcolor,fullbrightness);//Left Strand
	}
	FastLED.show();
	
	delay(3000);
	ResetToBlack();//Set leds back to black
}

void Lighting::AddressAllStrands(int H, int S, int V, bool show_update)
{
	for(int i = 0; i < NUM_STRANDS; i++)
	{
		for(int j = 0; j < NUM_LEDS; j++)
		{
			LedStrandArray[i][j].setHSV(H,S,V);
		}
	}
	if(show_update)
	{
		FastLED.show();
	}
}

void Lighting::AddressAllStrandsSingle(int led_num, int H, int S, int V, bool show_update)
{
	for(int i = 0; i < NUM_STRANDS; i++)
	{
			LedStrandArray[i][led_num].setHSV(H,S,V);
	}
	if(show_update)
	{
		FastLED.show();
	}
}

void Lighting::ResetToBlackBetween(int lowerRange, int upperRange){
  for(int i=lowerRange;i<=upperRange;i++){
    AddressAllStrandsSingle(i,0,0,0,false);
  }
  FastLED.show();
}


void AddressSingleStrand(int strand_num, int H, int S, int V, bool show_update = true)
{
	for(int i = 0; i<NUM_LEDS; i++)
	{
		LedStrandArray[strand_num][i].setHSV(H,S,V);
	}
	if(show_update)
	{
		FastLED.show();
	}
}

void AddressSingleStrandSingle(int strand_num, int led_num, int H, int S, int V, bool show_update = true)
{
	LedStrandArray[strand_num][led_num].setHSV(H,S,V);
	if(show_update)
	{
		FastLED.show();
	}
}






void Lighting::BusyPattern()
{
	for(int hue = 0; hue<=255; hue++)
	{
		AddressAllStrands(hue,255,255,false);
		delay(30);
		FastLED.show();
	}
}

void Lighting::BusyPattern2()
{
	for(int hue = 0; hue<=255; hue++)
	{
		for(int i = 0; i < NUM_LEDS; i++)
		{
			LedStrandArray[RightStrand][i].setHSV(hue,255,255);//Right Strand
			LedStrandArray[LeftStrand][i].setHSV(hue,255,255);//Left Strand
		}
		delay(30);
		FastLED.show();
	}
	for(int hue = 255; hue>=0; hue--)
	{
		for(int i = 0; i < NUM_LEDS; i++)
		{
			LedStrandArray[RightStrand][i].setHSV(hue,255,hue);//Right Strand
			LedStrandArray[LeftStrand][i].setHSV(hue,255,hue);//Left Strand
		}
		delay(30);
		FastLED.show();
	}
}