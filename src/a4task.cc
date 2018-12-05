/**
 * CMPUT 379 - Assignment 4
 * File Name: a4task.cc
 * Student Name: Jacob Bakker
 *
 *
 */

#include "a4tasks.h"


int main(int argc, char *argv[]) {
	Session * sess = NULL;
	HR_Clock::timepoint start_time = HR_Clock::now();

	try {
		sess = new Session(argc, argv, start_time);
		sess.run();
	} catch (Sess_Exception& e) { e.print_traceback(); }
}
