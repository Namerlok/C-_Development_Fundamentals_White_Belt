/*
 * date.cpp
 *
 *  Created on: 4 сент. 2020 г.
 *      Author: Zarka
 */
#include "date.h"


Date::Date(int new_year, int new_month, int new_day) {
	year = new_year;
	if (new_month > 12 || new_month < 1) {
		throw logic_error("Month value is invalid: " + to_string(new_month));
	}
	month = new_month;
	if (new_day > 31 || new_day < 1) {
		throw logic_error("Day value is invalid: " + to_string(new_day));
	}
	day = new_day;
}

int Date::GetYear() const {
	return year;
}

int Date::GetMonth() const {
	return month;
}

int Date::GetDay() const {
	return day;
}

ostream& operator<<(ostream& stream, const Date& date) {
  stream << setw(4) << setfill('0') << date.GetYear() <<
      "-" << setw(2) << setfill('0') << date.GetMonth() <<
      "-" << setw(2) << setfill('0') << date.GetDay();
  return stream;
}

bool operator<(const Date& lhs, const Date& rhs) {
  return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
      vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator>(const Date& lhs, const Date& rhs) {
	return rhs < lhs;
}

bool operator==(const Date& lhs, const Date& rhs) {
	return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} ==
		vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator!=(const Date& lhs, const Date& rhs) {
	return !(lhs == rhs);
}

bool operator<=(const Date& lhs, const Date& rhs) {
	return (lhs < rhs) || (lhs == rhs);
}

bool operator>=(const Date& lhs, const Date& rhs) {
	return rhs <= lhs;
}


Date ParseDate(istream& is) {

	int year = 0, month = 0, day = 0;

	is >> year;
	is.ignore(1);

	is >> month;
	is.ignore(1);

	is >> day;

	return Date(year, month, day);
}

/* авторское решение
#include "date.h"

#include <iomanip>
#include <tuple>
using namespace std;

Date ParseDate(istream& is) {
  Date result;
  is >> result.year;
  is.ignore(1);
  is >> result.month;
  is.ignore(1);
  is >> result.day;
  return result;
}

ostream& operator << (ostream& os, const Date& date) {
  os << setw(4) << setfill('0') << date.year << '-'
     << setw(2) << setfill('0') << date.month << '-'
     << setw(2) << setfill('0') << date.day;
  return os;
}

bool operator == (const Date& lhs, const Date& rhs) {
  return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}

bool operator != (const Date& lhs, const Date& rhs) {
  return tie(lhs.year, lhs.month, lhs.day) != tie(rhs.year, rhs.month, rhs.day);
}

bool operator < (const Date& lhs, const Date& rhs) {
  return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
}

bool operator <= (const Date& lhs, const Date& rhs) {
  return tie(lhs.year, lhs.month, lhs.day) <= tie(rhs.year, rhs.month, rhs.day);
}

bool operator > (const Date& lhs, const Date& rhs) {
  return tie(lhs.year, lhs.month, lhs.day) > tie(rhs.year, rhs.month, rhs.day);
}

bool operator >= (const Date& lhs, const Date& rhs) {
  return tie(lhs.year, lhs.month, lhs.day) >= tie(rhs.year, rhs.month, rhs.day);
}
 */

