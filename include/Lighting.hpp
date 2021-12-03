#ifndef Lighting_HPP
#define Lighting_HPP
#include <FastLED.h>

///////////////////////////FastLED Defines
FASTLED_USING_NAMESPACE
#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif
/////////
#define RightStrandPin   14 //used to be 5 for silk screen mapping, now 14 for esp8266 chip pin mapping idk what changed
#define LeftStrandPin    12//used to be 6 for silk screen mapping, now 12 for esp8266 chip pin mapping idk what changed

#define NUM_STRANDS 2 //Defined from Right to Left
#define NUM_LEDS 50

#define CHIPSET_TYPE WS2811
#define COLOR_ORDER RGB

#define BRIGHTNESS         255//96 was the original value
#define FRAMES_PER_SECOND  120//Maybe I'll use this one day

#define TO_SECONDS 1000 //Used to change delays to seconds
//////////////////////////

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
extern int zerocolor;
extern int quarterbrightness;
extern int halfbrightness;
extern int fullbrightness;
extern int black;
extern int white;
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