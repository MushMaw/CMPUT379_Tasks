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

	try {
		sess = new Session(argc, argv);
		sess->run();
		delete sess;
	} catch (Sess_Exception& e) { e.print_msg_traceback(); }
}
