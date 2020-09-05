/*
 * test_runner.cpp
 *
 *  Created on: 4 сент. 2020 г.
 *      Author: Zarka
 */

#include "test_runner.h"

TestRunner::~TestRunner() {
	if (fail_count > 0) {
		cerr << fail_count << " unit tests failed. Terminate" << endl;
		exit(1);
	}
}

void Assert(bool b, const string& hint) {
	AssertEqual(b, true, hint);
}

