#include "DynamicEffects.hpp"
#include "Timing.hpp"

#include <stdlib.h>//Rand functions

Timing effect_timer;

using namespace Colors;

DynamicEffects::DynamicEffects()
{
	//Seed the rand() function
	srand(effect_timer.GetProgramEpoch()*rand()%511 + 23312721);
	ResetMbrVars();
	InitChristmasColors();//Load colors into christmas colors array
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
	m_init_state = true;
}

//Effects

void DynamicEffects::InitChristmasColors()
{
for(int i = 0; i < NUM_LEDS; i+=5)
{
//Set first led to red, second to blue, third to green, fourth to yellow, and fifth to pink
//These colors are chosen to closely match thos of old incandescent colored Christmas lights
		m_old_christmas_colors[i] = 0;//Default Red Val is 0
		m_old_christmas_colors[i+1] = 160;//Default Blue Val is 160
		m_old_christmas_colors[i+2] = 86;//Default Green Val is 96
		m_old_christmas_colors[i+3] = 44;//Default Yellow Val is 64
		m_old_christmas_colors[i+4] = 245;//Default Pink Val is 224
}
}


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
		effect_timer.ResetElapsedTime();/*This Reset has to be at the top to reset the time right away to keep the time between the different
										bightness setting the same. If it was at the bottom, it would be a consistent time between calls. Up here,
										it starts recording while the fade op is going on. This way there is a consitent delay from each each execution
										 and call of the function, not just between function calls. We don't limit the color range normally,
										 so we should keep the Reset method ad the bottom unless we decide to only use a small color range.*/

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
		AddressAllStrands(rand()%256,S,V);
		effect_timer.ResetElapsedTime();
	}
}

void DynamicEffects::RandomColorCycle(int dly, int S, int V)
{
	if(effect_timer.GetElapsedTime() > dly)
	{
		if(m_init_state)
		{
		m_val_storage[0][0] = rand()%256;//create a random color and store it in a universal value storage array
		m_current_color = rand()%256;
			m_init_state = false;
		}

		if(m_init_state == false)
		{
			if(m_current_color < m_val_storage[0][0])//REM: there is an array of 16 integer values for each strand
			{
				AddressAllStrands(m_current_color,S,V);
				m_current_color++;
			}
			else if(m_current_color > m_val_storage[0][0])
			{
				AddressAllStrands(m_current_color,S,V);
				m_current_color--;
			}
			else if(m_current_color == m_val_storage[0][0])
			{
				m_val_storage[0][0] = rand()%256;
			}
		}
		effect_timer.ResetElapsedTime();
	}
}

void DynamicEffects::RandomColorsAll(int dly, int S, int V)
{
	if(effect_timer.GetElapsedTime() > dly)
	{
		
		for(int i = 0; i < NUM_STRANDS; i++)
		{	
			for(int j = 0; j < NUM_LEDS; j++)
			{
				AddressSingleStrandSingle(i,j,rand()%256,S,V,false);
			}
		}
		FastLED.show();
		effect_timer.ResetElapsedTime();
	}
}

void DynamicEffects::RandomColorsAllFading(int dly, int S, int V)
{
	if(effect_timer.GetElapsedTime() > dly)
	{
		if(m_init_state)
		{
			for(int i = 0; i < NUM_STRANDS; i++)//Initialize all Leds to random colors
			{
				for(int j = 0; j < NUM_LEDS; j++)
				{
					m_led_array_storage[0][i][j] = rand()%256;//Set values for fade from
					AddressSingleStrandSingle(i,j,m_led_array_storage[0][i][j],S,V,false);
				}
			}

			for(int i = 0; i < NUM_STRANDS; i++)//Set Each Led to have two random values to fade between
			{
				for(int j = 0; j < NUM_LEDS; j++)//Using second of 16 strand arrays to hold hue values to fade to
				{
					m_led_array_storage[1][i][j] = rand()%256;//Set values for fade to
				}
			}
			FastLED.show();
			m_init_state = false;
		}

		if(m_init_state == false)
		{
			for(int i = 0; i < NUM_STRANDS; i++)//Iterate through each led and change its value by one closer to the second fade val
			{
				for(int j = 0; j < NUM_LEDS; j++)
				{
					if(m_led_array_storage[0][i][j] < m_led_array_storage[1][i][j])//REM: Use the first two arrays of Led arrays to hold hue vals
					{
						AddressSingleStrandSingle(i,j,m_led_array_storage[0][i][j],S,V,false);//Set single led to its stored array value
						m_led_array_storage[0][i][j]++;
					}
					else if(m_led_array_storage[0][i][j] > m_led_array_storage[1][i][j])//REM: Use the first two arrays of Led arrays to hold hue vals
					{
						AddressSingleStrandSingle(i,j,m_led_array_storage[0][i][j],S,V,false);//Set single led to its stored array value
						m_led_array_storage[0][i][j]--;
					}
					else if(m_led_array_storage[0][i][j] == m_led_array_storage[1][i][j])//REM: Use the first two arrays of Led arrays to hold hue vals
					{
						m_led_array_storage[1][i][j] = rand()%256;//Set new value for fade to					
					}

				}
			}
			FastLED.show();
			effect_timer.ResetElapsedTime();
		}
	}
}

void DynamicEffects::RandomAllValsFade(int dly)
{
	if(effect_timer.GetElapsedTime() > dly)
	{
		if(m_init_state)
		{
			for(int i = 0; i < NUM_STRANDS; i++)//Initialize all Leds to random colors
			{
				for(int j = 0; j < NUM_LEDS; j++)
				{
					m_led_array_storage[0][i][j] = rand()%256;//Set values for fade from
					m_led_array_storage[2][i][j] = rand()%256;//Set values for saturation to fade from
					m_led_array_storage[4][i][j] = rand()%256;//Set values for brightness to fade from
					AddressSingleStrandSingle(i,j,m_led_array_storage[0][i][j],m_led_array_storage[2][i][j],m_led_array_storage[4][i][j],false);
				}
			}

			for(int i = 0; i < NUM_STRANDS; i++)//Set Each Led to have two random values to fade between
			{
				for(int j = 0; j < NUM_LEDS; j++)//Using second of 16 strand arrays to hold hue values to fade to
				{
					m_led_array_storage[1][i][j] = rand()%256;//Set values for fade to
					m_led_array_storage[3][i][j] = rand()%256;//Set sat values for fade to
					m_led_array_storage[5][i][j] = rand()%256;//Set brightness values for fade to
				}
			}
			FastLED.show();
			m_init_state = false;
		}

		if(m_init_state == false)
		{
			for(int i = 0; i < NUM_STRANDS; i++)//Iterate through each led and change its value by one closer to the second fade val
			{
				for(int j = 0; j < NUM_LEDS; j++)
				{
					if(m_led_array_storage[0][i][j] < m_led_array_storage[1][i][j])//REM: Use the first two arrays of Led arrays to hold hue vals
					{
						m_led_array_storage[0][i][j]++;
					}
					else if(m_led_array_storage[0][i][j] > m_led_array_storage[1][i][j])//REM: Use the first two arrays of Led arrays to hold hue vals
					{
						m_led_array_storage[0][i][j]--;
					}
					else if(m_led_array_storage[0][i][j] == m_led_array_storage[1][i][j])//REM: Use the first two arrays of Led arrays to hold hue vals
					{
						m_led_array_storage[1][i][j] = rand()%256;//Set new value for fade to					
					}
					
					//Sat Vals
					if(m_led_array_storage[2][i][j] < m_led_array_storage[3][i][j])//REM: Use the next two arrays of Led arrays to hold sat vals
					{
						m_led_array_storage[2][i][j]++;
					}
					else if(m_led_array_storage[2][i][j] > m_led_array_storage[3][i][j])//REM: Use the next two arrays of Led arrays to hold sat vals
					{
						m_led_array_storage[2][i][j]--;
					}
					else if(m_led_array_storage[2][i][j] == m_led_array_storage[3][i][j])//REM: Use the next two arrays of Led arrays to hold sat vals
					{
						m_led_array_storage[3][i][j] = rand()%256;//Set new value for fade to					
					}

					//Brightness Vals
					if(m_led_array_storage[4][i][j] < m_led_array_storage[5][i][j])//REM: Use the next two arrays of Led arrays to hold sat vals
					{
						m_led_array_storage[4][i][j]++;
					}
					else if(m_led_array_storage[4][i][j] > m_led_array_storage[5][i][j])//REM: Use the next two arrays of Led arrays to hold sat vals
					{
						m_led_array_storage[4][i][j]--;
					}
					else if(m_led_array_storage[4][i][j] == m_led_array_storage[5][i][j])//REM: Use the next two arrays of Led arrays to hold sat vals
					{
						m_led_array_storage[5][i][j] = rand()%256;//Set new value for fade to					
					}

					AddressSingleStrandSingle(i,j,m_led_array_storage[0][i][j],m_led_array_storage[2][i][j],m_led_array_storage[4][i][j],false);
				}
			}
			FastLED.show();
			effect_timer.ResetElapsedTime();
		}
	}
}

/*
*
*Christmas Effects
*
*/

void DynamicEffects::ChristmasOriginalBreathing(int dly, int max_brightness)
{
	if(effect_timer.GetElapsedTime() > dly * (fullbrightness/max_brightness))//set fade times to be equivalent between brightness levels
	{
		effect_timer.ResetElapsedTime();/*This Reset has to be at the top to reset the time right away to keep the time between the different
										bightness setting the same. If it was at the bottom, it would be a consistent time between calls. Up here,
										it starts recording while the fade op is going on. This way there is a consitent delay from each each execution
										 and call of the function, not just between function calls. We don't limit the color range normally,
										 so we should keep the Reset method ad the bottom unless we decide to only use a small color range.*/

		if(m_fade_state == false)
		{
			if(m_init_state)
			{	
				m_init_state = false;
				m_current_brightness = max_brightness;

				for(int i = 0; i < NUM_LEDS; i++)
					{
						AddressAllStrandsSingle(i, m_old_christmas_colors[i],Colors::fullcolor, m_current_brightness,false);
					}
					FastLED.show();
			}
			
			if(m_current_brightness >= max_brightness)//stop from fastled updating twice and causing a color pulse
			{
					m_current_brightness = max_brightness;
					m_fade_state = true;
			}
			else
			{
				for(int i = 0; i < NUM_LEDS; i++)
					{
						AddressAllStrandsSingle(i, m_old_christmas_colors[i],Colors::fullcolor, m_current_brightness,false);
					}
					FastLED.show();
				m_current_brightness++;
				m_fade_state = false;
			}
			
		}

		if(m_fade_state == true)
		{
			if(m_current_brightness <= 0)
			{
					m_current_brightness = 0;
					m_fade_state = false;
			}
			else
			{
				for(int i = 0; i < NUM_LEDS; i++)
					{
						AddressAllStrandsSingle(i, m_old_christmas_colors[i],Colors::fullcolor, m_current_brightness,false);
					}
					FastLED.show();
				m_current_brightness--;
				m_fade_state = true;
			}
			
		}
	}
}

void DynamicEffects::ChristmasOriginalTwinkling(int dly, int S, int max_brightness)
{
	if(effect_timer.GetElapsedTime() > dly)
	{
		if(m_init_state)
		{
			for(int i = 0; i < NUM_LEDS; i++)//Set LEDs to Christmas Color
					{
						AddressAllStrandsSingle(i, m_old_christmas_colors[i],Colors::fullcolor, max_brightness,false);
					}
					FastLED.show();

			for(int i = 0; i < NUM_STRANDS; i++)
			{
				m_val_storage[i][0] = rand()%NUM_LEDS;//Pick random LED to be faded and save the value
				m_val_storage[i][1] = max_brightness;//Set the leds temp brightness to full
				m_val_storage[i][2] = 0;//Use as twinkle fade indicator
			}

			m_init_state = false;	
		}

			for(int i = 0; i < NUM_STRANDS; i++)//Fading In-Out Loop
			{
					if(m_val_storage[i][1] > 0 && m_val_storage[i][2] == 0)//Fade out
					{
						AddressSingleStrandSingle(i,m_val_storage[i][0],m_old_christmas_colors[m_val_storage[i][0]],S,m_val_storage[i][1],false);
						m_val_storage[i][1]--;
					}
					else if(m_val_storage[i][1] == 0)//Check if faded out
					{
						m_val_storage[i][2] = 1;
					}

					if(m_val_storage[i][1] < max_brightness && m_val_storage[i][2] == 1)//Fade in
					{
						AddressSingleStrandSingle(i,m_val_storage[i][0],m_old_christmas_colors[m_val_storage[i][0]],S,m_val_storage[i][1],false);
						m_val_storage[i][1]++;
					}
					else if(m_val_storage[i][1] == max_brightness)//Check if fade in is complete
					{
						m_val_storage[i][0] = rand()%NUM_LEDS;//Set new random led to be twinkled
						m_val_storage[i][2] = 0;//reset twinkle state
					}
			}
		FastLED.show();
		effect_timer.ResetElapsedTime();//Reset Elapsed Timer
	}
}