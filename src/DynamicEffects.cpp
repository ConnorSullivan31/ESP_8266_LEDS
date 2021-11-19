#include "DynamicEffects.hpp"
#include "Timing.hpp"

#include <stdlib.h>//Rand functions

Timing effect_timer;

using namespace Colors;

DynamicEffects::DynamicEffects()
{
	//Seed the rand() function
	srand(effect_timer.GetProgramEpoch()*rand()%511 + 23242);
	ResetMbrVars();
	for(int i = 0; i < NUM_STRANDS; i++)
	{
		for(int j = 0; j < MAX_CLR_SV_ARR_SZ; j++)
		{
			m_val_sv[i][j] = 0;//Initialize array to zero
		}
	}
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
	m_first_call = true;
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

void DynamicEffects::RandomColorCycle(int dly, int S, int V)
{
	if(effect_timer.GetElapsedTime() > dly)
	{
		effect_timer.ResetElapsedTime();

		if(m_first_call)
		{
		m_val_sv[0][0] = rand()%255;//create a random color and store it in a universal value storage array
		m_current_color = rand()%255;
			m_first_call = false;
		}

		if(m_first_call == false)
		{
			if(m_current_color < m_val_sv[0][0])
			{
				AddressAllStrands(m_current_color,S,V);
				m_current_color++;
			}
			else if(m_current_color > m_val_sv[0][0])
			{
				AddressAllStrands(m_current_color,S,V);
				m_current_color--;
			}
			else if(m_current_color == m_val_sv[0][0])
			{
				m_val_sv[0][0] = rand()%255;
			}
		}
	}
}

void DynamicEffects::RandomColorsAll(int dly, int S, int V)
{
	if(effect_timer.GetElapsedTime() > dly)
	{
		effect_timer.ResetElapsedTime();
		
		for(int i = 0; i < NUM_STRANDS; i++)
		{	
			for(int j = 0; j < NUM_LEDS; j++)
			{
				AddressSingleStrandSingle(i,j,rand()%255,S,V,false);
			}
		}
		FastLED.show();
	}
}