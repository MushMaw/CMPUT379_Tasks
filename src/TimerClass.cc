/**
 * CMPUT 379 - Assignment 3
 * File Name: TimerClass.cc
 * Student Name: Jacob Bakker
 *
 * Implements a basic millisecond Timer for tracking the duration between the Timer's
 * start time and the current time.
 *
 * CITATION: This class is adapted from the "TimerClass" used in Assignment 3.
 */

#include "TimerClass.h"


/**
 * Timer Constructors
 */

Timer::Timer(HR_Clock::time_point start_time) { this->set_start_time(start_time); }
Timer::Timer() { this->start_time = HR_Clock::now(); }

/**
 * Getters and setters for start time.
 */

void Timer::set_start_time(HR_Clock::time_point tp) {
	this->start_time = tp;
}

HR_Clock::time_point Timer::get_start_time() { return this->start_time; }


/**
 * Function: get_duration
 * -----------------------
 * Returns the number of milliseconds that have passed between the current time
 * "curr_time" and the start time of the Timer instance.
 *
 * Parameters: 
 *	- curr_time: The current time.
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

/**
 * Function: get_duration
 * -----------------------
 * Returns the number of milliseconds that have passed between the current time
 * and the start time of the Timer instance.
 *
 * Parameters: None
 * Return Value: Duration in milliseconds.
 * Throws: None
 */
int Timer::get_duration() {
	HR_Clock::time_point curr_time = HR_Clock::now();
	return this->get_duration(curr_time);
}
