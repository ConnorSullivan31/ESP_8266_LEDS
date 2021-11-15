#include "Timing.hpp"
#include <Arduino.h>
Timing::Timing()
{
	start_time = 0;
	current_time = 0;
	previous_time = 0;
}

Timing::~Timing()
{

}

void Timing::ResetElapsedTime()
{
  current_time = millis();
  previous_time = current_time;
}
unsigned long long Timing::GetProgramEpoch()
{
	current_time = millis();
	return current_time - start_time;
}
unsigned long long Timing::GetElapsedTime()
{
	current_time = millis();
	return current_time - previous_time;
}