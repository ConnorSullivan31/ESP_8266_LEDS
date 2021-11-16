#include "StaticEffects.hpp"

using namespace Colors;

StaticEffects::StaticEffects()
{

}

StaticEffects::~StaticEffects()
{

}

void StaticEffects::StaticUSA()
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