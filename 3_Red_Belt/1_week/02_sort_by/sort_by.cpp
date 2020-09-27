//============================================================================
// Name        : sort_by.cpp
// Author      : Namerlok
// Version     :
// Copyright   : Your copyright notice
// Description : Ansi-style
//============================================================================

#include "airline_ticket.h"
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

#define SORT_BY(field)										\
[](const AirlineTicket& lhs, const AirlineTicket& rhs) {	\
	return lhs.field < rhs.field;}

void TestSortBy();
//void SortTickets(vector<AirlineTicket>& tixs);

bool operator== (const Date& d1, const Date& d2);
bool operator== (const Time& t1, const Time& t2);

bool operator< (const Date& d1, const Date& d2);
bool operator< (const Time& t1, const Time& t2);

ostream& operator<< (ostream& out, const Date& d);
ostream& operator<< (ostream& out, const Time& t);

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestSortBy);
}

void TestSortBy() {
	vector<AirlineTicket> tixs = {
			{"VKO", "AER", "Utair",     {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20,  0}, 1200},
			{"AER", "VKO", "Utair",     {2018, 3,  5}, {14, 15}, {2018, 3,  5}, {16, 30}, 1700},
			{"AER", "SVO", "Aeroflot",  {2018, 3,  5}, {18, 30}, {2018, 3,  5}, {20, 30}, 2300},
			{"PMI", "DME", "Iberia",    {2018, 2,  8}, {23, 00}, {2018, 2,  9}, { 3, 30}, 9000},
			{"CDG", "SVO", "AirFrance", {2018, 3,  1}, {13, 00}, {2018, 3,  1}, {17, 30}, 8000},
		};

	sort(begin(tixs), end(tixs), SORT_BY(price));
	ASSERT_EQUAL(tixs.front().price, 1200);
	ASSERT_EQUAL(tixs.back().price, 9000);

	sort(begin(tixs), end(tixs), SORT_BY(from));
	ASSERT_EQUAL(tixs.front().from, "AER");
	ASSERT_EQUAL(tixs.back().from, "VKO");

	sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
	ASSERT_EQUAL(tixs.front().arrival_date, (Date{2018, 2, 9}));
	ASSERT_EQUAL(tixs.back().arrival_date, (Date{2018, 3, 5}));
}

bool operator== (const Date& d1, const Date& d2) {
	return (d1.year == d2.year && d1.month == d2.month && d1.day == d2.day)
			? true : false;
}

bool operator== (const Time& t1, const Time& t2) {
	return (t1.hours == t2.hours && t1.minutes == t2.minutes)
			? true : false;
}

bool operator< (const Date& d1, const Date& d2) {
	if (d1.year > d2.year)
		return false;

	if (d1.year ==  d2.year && d1.month > d2.month)
		return false;

	if (d1.year ==  d2.year && d1.month == d2.month && d1.day >=  d2.day)
		return false;

	return true;
}

bool operator< (const Time& t1, const Time& t2) {
	if (t1.hours > t2.hours)
		return false;

	if (t1.hours == t2.hours && t1.minutes >= t2.minutes)
		return false;

	return true;
}

ostream& operator<< (ostream& out, const Date& d) {
	out << d.year << "-" << d.month << "-" << d.day;
	return out;
}

ostream& operator<< (ostream& out, const Time& t) {
	out << t.hours << ":" << t.minutes;
	return out;
}

/*
void SortTickets(vector<AirlineTicket>& tixs) {
	stable_sort(begin(tixs), end(tixs), SORT_BY(to));
	stable_sort(begin(tixs), end(tixs), SORT_BY(departure_time));
	stable_sort(begin(tixs), end(tixs), SORT_BY(price));
}


void SortTickets(vector<AirlineTicket>& tixs) {
	stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
		return lhs.to < rhs.to;});

	stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
		return lhs.departure_time < rhs.departure_time;});

	stable_sort(begin(tixs), end(tixs), [](const AirlineTicket& lhs, const AirlineTicket& rhs) {
		return lhs.price < rhs.price;});
}
*/

/*авторское решение
#include "airline_ticket.h"
#include <iostream>
#include <tuple>
using namespace std;

bool operator < (const Date& lhs, const Date& rhs) {
  return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
}

bool operator == (const Date& lhs, const Date& rhs) {
  return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}

bool operator < (const Time& lhs, const Time& rhs) {
  return tie(lhs.hours, lhs.minutes) < tie(rhs.hours, rhs.minutes);
}

bool operator == (const Time& lhs, const Time& rhs) {
  return tie(lhs.hours, lhs.minutes) == tie(rhs.hours, rhs.minutes);
}

ostream& operator<<(ostream& os, const Date& d) {
  return os << d.year << '-' << d.month << '-' << d.day;
}

ostream& operator<<(ostream& os, const Time& t) {
  return os << t.hours << ':' << t.minutes;
}

#define SORT_BY(field)                                   \
[](const AirlineTicket& lhs, const AirlineTicket& rhs) { \
  return lhs.field < rhs.field;                          \
}
 */

