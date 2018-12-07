/**
 * CMPUT 379 - Assignment 4
 * File Name: TimerClass.h
 * Student Name: Jacob Bakker
 *
 * Implements a basic millisecond Timer.
 *
 * The Timer can be started with a target duration value given, allowing
 * for a program to query the Timer about whether the target duration has
 * been reached since having started it.
 */

#if !defined(TIMER_CLASS_H)
#define TIMER_CLASS_H 1

#include <chrono>

typedef std::chrono::high_resolution_clock HR_Clock;
typedef std::chrono::milliseconds millisec;
typedef std::chrono::duration<double> raw_duration;

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
