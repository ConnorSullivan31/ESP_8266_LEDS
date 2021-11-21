#include "StaticEffects.hpp"

using namespace Colors;

StaticEffects::StaticEffects()
{
	InitChristmasColors();
}

StaticEffects::~StaticEffects()
{

}

void StaticEffects::InitChristmasColors()
{
for(int i = 0; i < NUM_LEDS; i+=5)
{
//Set first led to red, second to blue, third to green, fourth to yellow, and fifth to pink
//These colors are chosen to closely match thos of old incandescent colored Christmas lights
		m_old_christmas_colors[i] = 0;//Default Red Val is 0
		m_old_christmas_colors[i+1] = 160;//Default Blue Val is 160
		m_old_christmas_colors[i+2] = 86;//Default Green Val is 96
		m_old_christmas_colors[i+3] = 44;//Default Yellow Val is 64
		m_old_christmas_colors[i+4] = 245;//Default Pink Val is 224
}
}

void StaticEffects::USARedWhiteBlue()
{
	for(int i = 0; i < NUM_LEDS; i+=3)
	{

		AddressAllStrandsSingle(i,red,fullcolor,fullbrightness,false);
	}
	for(int i = 1; i < NUM_LEDS; i+=3)
	{

		AddressAllStrandsSingle(i,zerocolor,zerocolor,fullbrightness,false);
	}
	for(int i = 2; i < NUM_LEDS; i+=3)
	{

		AddressAllStrandsSingle(i,blue,fullcolor,fullbrightness,false);
	}
	FastLED.show();
}

/*
*
*Christmas Effects
*
*/
void StaticEffects::ChristmasOriginal(int S, int V)
{
	for(int i = 0; i< NUM_LEDS; i++)
	{
		AddressAllStrandsSingle(i,m_old_christmas_colors[i],S,V,false);
	}
	FastLED.show();
}

void StaticEffects::PeppermintRWG()
{
	for(int i = 0; i < NUM_LEDS; i+=3)
	{

		AddressAllStrandsSingle(i,red,fullcolor,fullbrightness,false);
	}
	for(int i = 1; i < NUM_LEDS; i+=3)
	{

		AddressAllStrandsSingle(i,zerocolor,zerocolor,fullbrightness,false);
	}
	for(int i = 2; i < NUM_LEDS; i+=3)
	{

		AddressAllStrandsSingle(i,green,fullcolor,fullbrightness,false);
	}
	FastLED.show();
}

void StaticEffects::PeppermintRW()
{
	for(int i = 0; i < NUM_LEDS; i+=2)
	{

		AddressAllStrandsSingle(i,red,fullcolor,fullbrightness,false);
	}
	for(int i = 1; i < NUM_LEDS; i+=2)
	{

		AddressAllStrandsSingle(i,zerocolor,zerocolor,fullbrightness,false);
	}
	FastLED.show();
}

void StaticEffects::PeppermintRG()
{
	for(int i = 0; i < NUM_LEDS; i+=2)
	{

		AddressAllStrandsSingle(i,red,fullcolor,fullbrightness,false);
	}
	for(int i = 1; i < NUM_LEDS; i+=2)
	{

		AddressAllStrandsSingle(i,green,fullcolor,fullbrightness,false);
	}
	FastLED.show();
}

void StaticEffects::PeppermintGW()
{
	for(int i = 0; i < NUM_LEDS; i+=2)
	{

		AddressAllStrandsSingle(i,green,fullcolor,fullbrightness,false);
	}
	for(int i = 1; i < NUM_LEDS; i+=2)
	{

		AddressAllStrandsSingle(i,zerocolor,zerocolor,fullbrightness,false);
	}
	FastLED.show();
}

void StaticEffects::ShowColor(int clr)
{
	AddressAllStrands(clr,255,255);
}

void  StaticEffects::ShowTwoColors(int clr1, int clr2)
{
	for(int i = 0; i < NUM_STRANDS; i++)
	{
		if((i+2)%2==0)
		{
			AddressSingleStrand(i, clr1,255,255);
		}
		else
		{
			AddressSingleStrand(i, clr2, 255,255);
		}
	}
}