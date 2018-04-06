#pragma once

#include <ctime>
#include <chrono>

/* Timer class that starts a timer when it is instantiated */
class Timer {
public:
	/* Constructors & Destructor */
	Timer();

	/* Time Retrieval */
	virtual double elapsed();

protected:
	std::chrono::high_resolution_clock::time_point start_time, current_time;

};

/* Derivate of Timer that returns the time after dividing 1 by it */
class Fps : public Timer {
public:
	/* Time Retrieval */
	double elapsed() override;
};

