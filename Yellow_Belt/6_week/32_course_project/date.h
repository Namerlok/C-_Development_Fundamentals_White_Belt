/*
 * date.h
 *
 *  Created on: 4 сент. 2020 г.
 *      Author: Zarka
 */
#pragma once

#ifndef DATE_H_
#define DATE_H_

#include <iostream>
#include <istream>
#include <iomanip>
#include <vector>

using namespace std;

class Date{
public:
	Date(int new_year, int new_month, int new_day);

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

private:
	int year;
	int month;
	int day;
};

ostream& operator<<(ostream& stream, const Date& date);
bool operator<(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);

Date ParseDate(istream& is);

void TestDate();

#endif /* DATE_H_ */


/* авторское решение
#pragma once

#include <iostream>

using namespace std;

struct Date {
  int year, month, day;
};

ostream& operator << (ostream& os, const Date& date);
bool operator == (const Date& lhs, const Date& rhs);
bool operator != (const Date& lhs, const Date& rhs);
bool operator < (const Date& lhs, const Date& rhs);
bool operator <= (const Date& lhs, const Date& rhs);
bool operator > (const Date& lhs, const Date& rhs);
bool operator >= (const Date& lhs, const Date& rhs);

Date ParseDate(istream& is);

// Tests
void TestDateOutput();
void TestParseDate();
 */

