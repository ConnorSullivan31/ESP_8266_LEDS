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

	void ResetToBlackBetween(int lowerRange, int upperRange);
	void AddressAllStrands(int H, int S, int V, bool show_update = true);
	void AddressAllStrandsSingle(int led_num, int H, int S, int V, bool show_update = true);
	void AddressSingleStrand(int strand_num, int H, int S, int V, bool show_update = true);
	void AddressSingleStrandSingle(int strand_num, int led_num, int H, int S, int V, bool show_update = true);

protected:

private:

};







#endif//Lighting_HPP