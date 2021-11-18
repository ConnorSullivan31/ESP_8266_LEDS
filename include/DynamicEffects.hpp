#ifndef DYNAMICEFFECTS_HPP
#define DYNAMICEFFECTS_HPP
#include <stdarg.h>
#include <FastLED.h>
#include "Lighting.hpp"

class DynamicEffects : public Lighting
{
public:
	DynamicEffects();
	~DynamicEffects();

	//Effects
	void CycleColorList(int S,int V, int dly, int clr_cnt, ...);
	void ColorCycle();

protected:

private:
	int m_led_color;
	int m_step_counter;
};




#endif //DYNAMICEFFECTS_HPP