#ifndef Lighting_HPP
#define Lighting_HPP
#include <FastLED.h>

class Lighting
{
public:
	Lighting();
	~Lighting();
	void InitFastLED();
	void ResetToBlack(bool show_reset = true);
	void TestStrands();
	void BusyPattern();

protected:

private:
	int pin;

};







#endif//Lighting_HPP