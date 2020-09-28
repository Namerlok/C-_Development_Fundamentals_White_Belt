//============================================================================
// Name        : print_values.cpp
// Author      : Namerlok
// Version     :
// Copyright   : Your copyright notice
// Description : Ansi-style
//============================================================================

#include "test_runner.h"

#include <iostream>
#include <ostream>

using namespace std;

#define PRINT_VALUES(out, x, y) (out) << (x) << endl << (y) << endl


int main() {
	TestRunner tr;
	tr.RunTest([] {
		ostringstream output;
		PRINT_VALUES(output, 5, "red belt");
		ASSERT_EQUAL(output.str(), "5\nred belt\n");
	}, "PRINT_VALUES usage example");
}


