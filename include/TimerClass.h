/**
 * CMPUT 379 - Assignment 4
 * File Name: TimerClass.h
 * Student Name: Jacob Bakker
 *
 * Implements a basic millisecond Timer for tracking the duration between the Timer's
 * start time and the current time.
 *
 * CITATION: This class is adapted from the "TimerClass" used in Assignment 3.
 */

#if !defined(TIMER_CLASS_H)
#define TIMER_CLASS_H 1

#include <chrono>
#include "a4constants.h"

class Timer {
	private:
		HR_Clock::time_point start_time;
	public:
		Timer();
		Timer(HR_Clock::time_point start_time);
		int get_duration(HR_Clock::time_point curr_time);
		int get_duration();
		void set_start_time(HR_Clock::time_point tp);
		HR_Clock::time_point get_start_time();
};

#endif
