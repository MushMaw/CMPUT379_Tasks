/**
 * CMPUT 379 - Assignment 3
 * File Name: TimerClass.cc
 * Student Name: Jacob Bakker
 *
 * Implements a basic millisecond Timer.
 *
 * The Timer can be started with a target duration value given, allowing
 * for a program to query the Timer about whether the target duration has
 * been reached since having started it.
 */

#include "TimerClass.h"


/**
 * Timer Constructor
 */

Timer::Timer(HR_Clock::time_point start_time) { this->set_start_time(start_time); }
Timer::Timer() { this->start_time = HR_Clock::now(); }

/**
 * Function: get_duration
 * -----------------------
 * 
 *
 * Parameters: 
 *	- start: Start time.
 *	- end: End time.
 * Return Value: Duration in milliseconds.
 * Throws: None
 */
int Timer::get_duration(HR_Clock::time_point curr_time) {
	millisec ms_dur;
	raw_duration raw_dur;
	int ms;

	raw_dur = std::chrono::duration_cast<raw_duration>(curr_time - this->start_time);
	ms_dur = std::chrono::duration_cast<millisec>(raw_dur);
	ms = ms_dur.count();

	return ms;
}

int Timer::get_duration() {
	HR_Clock::time_point curr_time = HR_Clock::now();
	return this->get_duration(curr_time);
}

void Timer::set_start_time(HR_Clock::time_point tp) {
	this->start_time = tp;
}

HR_Clock::time_point Timer::get_start_time() { return this->start_time; }


