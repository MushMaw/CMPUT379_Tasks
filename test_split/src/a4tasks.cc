/**
 * CMPUT 379 - Assignment 4
 * File Name: a4tasks.cc
 * Student Name: Jacob Bakker
 *
 *
 */

#include "a4tasks.h"


int main(int argc, char *argv[]) {
	Session * sess = NULL;
	//HR_Clock::time_point start_time = HR_Clock::now();

	try {
		sess = new Session(argc, argv);//, start_time);
		sess->run();
		delete sess;
	} catch (Sess_Exception& e) { e.print_msg_traceback(); }
}
