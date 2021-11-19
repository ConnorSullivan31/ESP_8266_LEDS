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

	void ResetMbrVars();
	//Effects
	void CycleColorList(int S,int V, int dly, int clr_cnt, ...);
	void ColorCycle();
	void BreathingColorCycle(int dly, int clr_step, int S = 255, int max_brightness = 63);

protected:

private:
	int m_current_led;
	int m_current_color;
	int m_current_brightness;
	int m_step_counter;
	bool m_fade_state;
};




#endif //DYNAMICEFFECTS_HPP