#ifndef Lighting_HPP
#define Lighting_HPP
#include <FastLED.h>

class Lighting
{
public:
	Lighting();
	~Lighting();
	void InitFastLED();
	void TestStrands();
	void BusyPattern();

protected:

private:
	int pin;

};







#endif//Lighting_HPP