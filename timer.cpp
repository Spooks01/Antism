#include "timer.h"

/* Constructors & Destructor */

Timer::Timer() 
{ 
	start_time = std::chrono::high_resolution_clock::now(); 
}

/* Time Retrieval */

double Timer::elapsed() 
{
	current_time = std::chrono::high_resolution_clock::now();

	return std::chrono::duration<double>(current_time - start_time).count();
}

/* Time Retrieval */

double Fps::elapsed() 
{
	current_time = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - start_time);
	start_time = current_time;

	return 1.0f / time_span.count();
}
