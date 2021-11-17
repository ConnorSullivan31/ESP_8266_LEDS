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
	void PeppermintRWG();
	void PeppermintRW();
	void PeppermintRG();
	void PeppermintGW();


protected:

private:


};



#endif // STATICEFFECTS_HPP