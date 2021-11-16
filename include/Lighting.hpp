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
	void BusyPattern2();

protected:

private:

};







#endif//Lighting_HPP