#include "Lighting.hpp"

////////////////////////All Pin info is in the header file. Only this and the CRGB array are setup here
//Create Strand Array
CRGB LedStrandArray[NUM_STRANDS][NUM_LEDS];//Order is Right to Left | Set size in headers
//////////////////////


//Create Color Namespace
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
int zerocolor=0;
int quarterbrightness=63;
int halfbrightness=127;
int fullbrightness=255;
int black=0;
int white=256;//Don't use this to set a value. For logic only
}

Lighting::Lighting()
{
ResetToBlack();
InitFastLED();
}

Lighting::~Lighting()
{
ResetToBlack();
}

void Lighting::InitFastLED()//All Pin info is in the header file. Only this and the CRGB array are setup here
{
	FastLED.addLeds<CHIPSET_TYPE, RightStrandPin, COLOR_ORDER>(LedStrandArray[0], NUM_LEDS).setCorrection(TypicalLEDStrip);//Right Strand
	FastLED.addLeds<CHIPSET_TYPE, LeftStrandPin, COLOR_ORDER>(LedStrandArray[1], NUM_LEDS).setCorrection(TypicalLEDStrip);//Left Strand
	/*
	*
	ADD ADDITIONAL STANDS HERE - SAME SETUP AS ABOVE
	*
	*/
	
	FastLED.setBrightness(BRIGHTNESS);
}

int Lighting::GetNumStrands()
{
	return NUM_STRANDS;
}

int Lighting::GetNumLeds()
{
	return NUM_LEDS;
}

//Basic Ops

void Lighting::ResetToBlack(bool show_reset)
{
	for(int i = 0; i < NUM_STRANDS; i++)
	{
		for(int j = 0; j < NUM_LEDS; j++)//Set LEDs to black
		{
		LedStrandArray[i][j] = CRGB::Black;
		}
	}
	if(show_reset)
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

void Lighting::TestStrands()
{
	using namespace Colors;

	ResetToBlack();//Set Leds to black and make sure there are no stored colors
	delay(10);//give leds a breather b4 starting up

	for(int i = 0; i < NUM_STRANDS; i++)
	{	
		for(int j = 0; j < NUM_LEDS; j++)//show all green and aqua as test
		{
			if((i+2)%2==0)
			{
				LedStrandArray[i][j].setHSV(green,fullcolor,fullbrightness);//Right Strand
			}
			else
			{
				LedStrandArray[i][j].setHSV(aqua,fullcolor,fullbrightness);//Left Strand
			}
		}
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


void Lighting::AddressSingleStrand(int strand_num, int H, int S, int V, bool show_update)
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

void Lighting::AddressSingleStrandSingle(int strand_num, int led_num, int H, int S, int V, bool show_update)
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
		for(int i = 0; i < NUM_STRANDS; i++)
		{
			for(int j = 0; j < NUM_LEDS; j++)
			{
				LedStrandArray[i][j].setHSV(hue,255,255);
			}
		}
		delay(30);
		FastLED.show();
	}
	for(int hue = 255; hue>=0; hue--)
	{
		for(int i = 0; i < NUM_STRANDS; i++)
		{
			for(int j = 0; j < NUM_LEDS; j++)
			{
				LedStrandArray[i][j].setHSV(hue,255,hue);
			}
		}
		delay(30);
		FastLED.show();
	}
}