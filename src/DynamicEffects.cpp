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
void DynamicEffects::CycleColorList(int S, int V, int dly, int clr_cnt, ...)
{
	int selected_clr;

	va_list p_arg_list;

	va_start(p_arg_list, clr_cnt);

	for(int i = 0; i<clr_cnt; i++)
	{	
		selected_clr = va_arg(p_arg_list, int);
		if(selected_clr == Colors::white)
		{
			AddressAllStrands(Colors::zerocolor,Colors::zerocolor,V);
			delay(dly);
		}
		else
		{
			AddressAllStrands(selected_clr,S,V);
			delay(dly);
		}

	}
	va_end(p_arg_list);
}

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