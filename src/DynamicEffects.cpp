#include "DynamicEffects.hpp"
#include "Timing.hpp"

#include <stdlib.h>//Rand functions

Timing effect_timer;

using namespace Colors;

DynamicEffects::DynamicEffects()
{
	ResetMbrVars();
}

DynamicEffects::~DynamicEffects()
{
	
}

void DynamicEffects::ResetMbrVars()//set all iteration variables here
{
	m_current_color = 0;
	m_step_counter = 0;
	m_current_led = 0;
	m_current_brightness = 0;
	m_fade_state = false;
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

void DynamicEffects::ColorCycle(int dly)
{	
	if(effect_timer.GetElapsedTime() > dly)
	{
		if(m_current_color <= 255)
		{
			AddressAllStrands(m_current_color,fullcolor,fullbrightness);
		}

		m_current_color++;

		if(m_current_color > 255)
		{
			m_current_color = 0;
		}
			effect_timer.ResetElapsedTime();
	}
}

void DynamicEffects::BreathingColorCycle(int dly, int clr_step, int S, int max_brightness)
{
	if(effect_timer.GetElapsedTime() > dly * (fullbrightness/max_brightness))//set fade times to be equivalent between brightness levels
	{
		effect_timer.ResetElapsedTime();

		if(m_fade_state == false)
		{
			if(m_current_brightness == max_brightness)//stop from fastled updating twice and causing a color pulse
			{
				AddressAllStrands(m_current_color,S,m_current_brightness,false);//dont update on last brightness before fade out starts
				m_current_brightness++;
				if(m_current_brightness > max_brightness)
				{
					m_fade_state = true;
					m_current_brightness = max_brightness;
				}
			}
			else
			{
				AddressAllStrands(m_current_color,S,m_current_brightness);
				m_current_brightness++;
				m_fade_state = false;
			}
			
		}

		if(m_fade_state == true)
		{
			if(m_current_brightness == 0)//stop from fastled updating twice and causing a color pulse
			{
				AddressAllStrands(m_current_color,S,m_current_brightness, false);//dont update on last brightness before fade in starts
				m_current_brightness--;
				if(m_current_brightness < 0)
				{
					m_fade_state = false;
					m_current_brightness = 0;
					m_current_color+= clr_step;
					if(m_current_color > 255)
					{
						m_current_color = 0;
					}
				}
			}
			else
			{
				AddressAllStrands(m_current_color,S,m_current_brightness);
				m_current_brightness--;
				m_fade_state = true;
			}
			
		}
	}
}

void DynamicEffects::RandomColor(int dly, int S, int V)
{
	if(effect_timer.GetElapsedTime() > dly)
	{
		AddressAllStrands(rand()%255,S,V);
		effect_timer.ResetElapsedTime();
	}
}

void DynamicEffects::RandomColorCycle(int dly)
{/*
	if(effect_timer.GetElapsedTime() > dly)
	{
		if(m_current_color <= 255)
		{
			AddressAllStrands(m_current_color,fullcolor,fullbrightness);
		}

		m_current_color++;

		if(m_current_color > 255)
		{
			m_current_color = 0;
		}
			effect_timer.ResetElapsedTime();
	}*/
}