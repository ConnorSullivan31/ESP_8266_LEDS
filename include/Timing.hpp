#ifndef TIMING_HPP
#define TIMING_HPP

class Timing
{
public:
	Timing();
	~Timing();

		void ResetElapsedTime();
		unsigned long long GetProgramEpoch();
		unsigned long long GetElapsedTime();

protected:
private:
unsigned long long current_time, previous_time, start_time;
};






#endif //TIMING_HPP