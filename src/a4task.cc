/**
 * CMPUT 379 - Assignment 4
 * File Name: a4tasks.cc
 * Student Name: Jacob Bakker
 *
 * Implements a basic main function for "a4tasks" program that simply
 * starts and runs a Session using command line input.
 */

#include "a4tasks.h"


int main(int argc, char *argv[]) {
	Session * sess = NULL;

	try {
		sess = new Session(argc, argv);
		sess->run();
		delete sess;
	} catch (Sess_Exception& e) { e.print_msg_traceback(); }
}
