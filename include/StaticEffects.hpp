#ifndef STATICEFFECTS_HPP
#define STATICEFFECTS_HPP
#include "Lighting.hpp"

class StaticEffects : public Lighting
{
public:
	StaticEffects();
	~StaticEffects();


	void ShowColor(int clr);
	void ShowTwoColors(int clr1, int clr2);

	void USARedWhiteBlue();

	//Christmas Colors
	void ChristmasOriginal(int S, int V);
	void PeppermintRWG();
	void PeppermintRW();
	void PeppermintRG();
	void PeppermintGW();


protected:

private:
	void InitChristmasColors();
int m_old_christmas_colors[NUM_LEDS];

};



#endif // STATICEFFECTS_HPP