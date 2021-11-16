#ifndef DYNAMICEFFECTS_HPP
#define DYNAMICEFFECTS_HPP
#include <FastLED.h>
#include "Lighting.hpp"

class DynamicEffects : public Lighting
{
public:
	DynamicEffects();
	~DynamicEffects();

	//Effects
	void ColorCycle();

protected:

private:
	int m_led_color;
};




#endif //DYNAMICEFFECTS_HPP