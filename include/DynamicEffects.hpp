#ifndef DYNAMICEFFECTS_HPP
#define DYNAMICEFFECTS_HPP
#include <stdarg.h>
#include <FastLED.h>
#include "Lighting.hpp"

#define MAX_CLR_SV_ARR_SZ 16

class DynamicEffects : public Lighting
{
public:
	DynamicEffects();
	~DynamicEffects();

	void ResetMbrVars();
	//Effects
	void CycleColorList(int S,int V, int dly, int clr_cnt, ...);
	void ColorCycle(int dly);
	void BreathingColorCycle(int dly, int clr_step, int S = 255, int max_brightness = 63);
	void RandomColor(int dly, int S, int V);//instantly changes all leds to a new random color
	void RandomColorCycle(int dly, int S, int V);//Fades all leds between colors like color cycle but in no order
	void RandomColorsAll(int dly, int S, int V);//instantly changes each leds to a new random color
	void RandomColorsAllFading(int dly, int S, int V);//Fades each led between colors
	void RandomAllValsFade(int dly);//Fades hue, sat, and val between each led
	//Christmas Effects
	void ChristmasOriginalBreathing(int dly, int max_brightness);
	void ChristmasOriginalTwinkling(int dly, int num_leds_to_twinkle, int S, int max_brightness);

protected:

private://Make Sure that these variables are reset between each effect call
		void InitChristmasColors();
	int m_current_led;
	int m_current_color;
	int m_current_brightness;
	int m_step_counter;
	bool m_fade_state;
	bool m_init_state;
	//Let the array save values in between resets
	int m_val_storage[NUM_STRANDS][MAX_CLR_SV_ARR_SZ];
	int m_led_array_storage[MAX_CLR_SV_ARR_SZ][NUM_STRANDS][NUM_LEDS];
	int m_old_christmas_colors[NUM_LEDS];
};




#endif //DYNAMICEFFECTS_HPP