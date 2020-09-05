/*
 * date_test.cpp
 *
 *  Created on: 4 сент. 2020 г.
 *      Author: Zarka
 */

#include "date.h"
#include "test_runner.h"
#include "sstream"

using namespace std;

void TestDate() {
	{
		istringstream is("2020-09-04");
		Date date = ParseDate(is);
		AssertEqual(date, Date(2020, 9, 4), "Parse date: 2020-09-04");
	}
	{
		istringstream is("1234-12-11");
		Date date = ParseDate(is);
		AssertEqual(date, Date(1234, 12, 11), "Parse date: 1234-12-11");

	}
	{
		istringstream is("1-1-1");
		Date date = ParseDate(is);
		AssertEqual(date, Date(1, 1, 1), "Parse date: 1-1-1");

	}
}

/* авторское решение
#include "date.h"
#include "test_runner.h"

#include <sstream>
using namespace std;

void TestDateOutput() {
  {
    ostringstream os;
    os << Date{2017, 11, 15};
    AssertEqual(os.str(), "2017-11-15", "Date output: simple");
  }
  {
    ostringstream os;
    os << Date{2017, 1, 1};
    AssertEqual(os.str(), "2017-01-01", "Date output: day and month less than 10");
  }
  {
    ostringstream os;
    os << Date{2, 10, 10};
    AssertEqual(os.str(), "0002-10-10", "Date output: year less than 1000");
  }
}

void TestParseDate() {
  istringstream is("2017-11-15");
  const Date date = ParseDate(is);

  AssertEqual(date.year, 2017, "Parse date: year");
  AssertEqual(date.month, 11, "Parse date: month");
  AssertEqual(date.day, 15, "Parse date: day");
}
 */
