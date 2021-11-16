#include "DynamicEffects.hpp"
#include "Timing.hpp"

Timing effect_timer;
using namespace Colors;

DynamicEffects::DynamicEffects()
{
	m_led_color = 0;
}

DynamicEffects::~DynamicEffects()
{
	
}

//Effects

void DynamicEffects::ColorCycle()
{	
	if(effect_timer.GetElapsedTime() > 30)
	{
		if(m_led_color <= 255)
		{
			AddressAllStrands(m_led_color,fullcolor,fullbrightness);
		}

		m_led_color++;

		if(m_led_color > 255)
		{
			m_led_color = 0;
		}
			effect_timer.ResetElapsedTime();
	}
}