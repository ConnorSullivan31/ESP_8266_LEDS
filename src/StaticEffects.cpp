#include "StaticEffects.hpp"

using namespace Colors;

StaticEffects::StaticEffects()
{

}

StaticEffects::~StaticEffects()
{

}

void StaticEffects::USARedWhiteBlue()
{
	for(int i = 0; i < GetNumLeds(); i+=3)
	{

		AddressAllStrandsSingle(i,red,fullcolor,fullbrightness,false);
	}
	for(int i = 1; i < GetNumLeds(); i+=3)
	{

		AddressAllStrandsSingle(i,white,white,fullbrightness,false);
	}
	for(int i = 2; i < GetNumLeds(); i+=3)
	{

		AddressAllStrandsSingle(i,blue,fullcolor,fullbrightness,false);
	}
	FastLED.show();
}

void StaticEffects::PeppermintRWG()
{
	for(int i = 0; i < GetNumLeds(); i+=3)
	{

		AddressAllStrandsSingle(i,red,fullcolor,fullbrightness,false);
	}
	for(int i = 1; i < GetNumLeds(); i+=3)
	{

		AddressAllStrandsSingle(i,white,white,fullbrightness,false);
	}
	for(int i = 2; i < GetNumLeds(); i+=3)
	{

		AddressAllStrandsSingle(i,green,fullcolor,fullbrightness,false);
	}
	FastLED.show();
}

void StaticEffects::PeppermintRW()
{
	for(int i = 0; i < GetNumLeds(); i+=2)
	{

		AddressAllStrandsSingle(i,red,fullcolor,fullbrightness,false);
	}
	for(int i = 1; i < GetNumLeds(); i+=2)
	{

		AddressAllStrandsSingle(i,white,white,fullbrightness,false);
	}
	FastLED.show();
}

void StaticEffects::PeppermintRG()
{
	for(int i = 0; i < GetNumLeds(); i+=2)
	{

		AddressAllStrandsSingle(i,red,fullcolor,fullbrightness,false);
	}
	for(int i = 1; i < GetNumLeds(); i+=2)
	{

		AddressAllStrandsSingle(i,green,fullcolor,fullbrightness,false);
	}
	FastLED.show();
}

void StaticEffects::PeppermintGW()
{
	for(int i = 0; i < GetNumLeds(); i+=2)
	{

		AddressAllStrandsSingle(i,green,fullcolor,fullbrightness,false);
	}
	for(int i = 1; i < GetNumLeds(); i+=2)
	{

		AddressAllStrandsSingle(i,white,white,fullbrightness,false);
	}
	FastLED.show();
}

void StaticEffects::ShowColor(int clr)
{
	AddressAllStrands(clr,255,255);
}

void  StaticEffects::ShowTwoColors(int clr1, int clr2)
{
	for(int i = 0; i < GetNumStrands(); i++)
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