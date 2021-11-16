#ifndef Lighting_HPP
#define Lighting_HPP
#include <FastLED.h>

namespace Colors
{
extern int red;
extern int orangeRed;
extern int orange;
extern int yellow;
extern int green;
extern int aqua;
extern int blue;
extern int purple;
extern int pink;
extern int fullcolor;
extern int halfcolor;
extern int white;
extern int quarterbrightness;
extern int halfbrightness;
extern int fullbrightness;
extern int black;
}

class Lighting
{
public:
	Lighting();
	~Lighting();
	void InitFastLED();
	int GetNumStrands();
	int GetNumLeds();

	void ResetToBlack(bool show_reset = true);
	void TestStrands();
	void BusyPattern();
	void BusyPattern2();

	void ResetToBlackBetween(int lowerRange, int upperRange);
	void AddressAllStrands(int H, int S, int V, bool show_update = true);
	void AddressAllStrandsSingle(int led_num, int H, int S, int V, bool show_update = true);
	void AddressSingleStrand(int strand_num, int H, int S, int V, bool show_update = true);
	void AddressSingleStrandSingle(int strand_num, int led_num, int H, int S, int V, bool show_update = true);

protected:

private:

};







#endif//Lighting_HPP