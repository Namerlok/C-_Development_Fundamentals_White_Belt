//============================================================================
// Name        : update_field.cpp
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
#include <tuple>
#include <map>
#include <set>

using namespace std;

#define SORT_BY(field)											\
	[](const AirlineTicket& lhs, const AirlineTicket& rhs) {	\
		return lhs.field < rhs.field;							\
	}

#define UPDATE_FIELD(ticket, field, values)	{		\
	auto it = values.find(#field);					\
	if (it != values.end()) {						\
		istringstream is(values.at(#field));		\
		is >> ticket.field;							\
	}												\
}



void TestSortBy();
void TestUpdate();

bool operator== (const Date& lhs, const Date& rhs);
bool operator== (const Time& lhs, const Time& rhs);

bool operator< (const Date& lhs, const Date& rhs);
bool operator< (const Time& lhs, const Time& rhs);

ostream& operator<< (ostream& out, const Date& d);
ostream& operator<< (ostream& out, const Time& t);

istream& operator>>(istream& is, Time& t);
istream& operator>>(istream& is, Date& d);


int main() {
	TestRunner tr;
	RUN_TEST(tr, TestSortBy);
	RUN_TEST(tr, TestUpdate);
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

void TestUpdate() {
	AirlineTicket t;
	t.price = 0;

	const map<string, string> updates1 = {
			{"departure_date", "2018-2-28"},
			{"departure_time", "17:40"},
		};
	UPDATE_FIELD(t, departure_date, updates1);
	UPDATE_FIELD(t, departure_time, updates1);
	UPDATE_FIELD(t, price, updates1);

	ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
	ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
	ASSERT_EQUAL(t.price, 0);

	const map<string, string> updates2 = {
			{"price", "12550"},
			{"arrival_time", "20:33"},
		};
	UPDATE_FIELD(t, departure_date, updates2);
	UPDATE_FIELD(t, departure_time, updates2);
	UPDATE_FIELD(t, arrival_time, updates2);
	UPDATE_FIELD(t, price, updates2);

	// updates2 не содержит ключей "departure_date" и "departure_time", поэтому
	// значения этих полей не должны измениться
	ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
	ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
	ASSERT_EQUAL(t.price, 12550);
	ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

bool operator== (const Date& lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}

bool operator== (const Time& lhs, const Time& rhs) {
	return tie(lhs.hours, lhs.minutes) == tie(rhs.hours, rhs.minutes);
}

bool operator< (const Date& lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
}

bool operator< (const Time& lhs, const Time& rhs) {
	return tie(lhs.hours, lhs.minutes) < tie(rhs.hours, rhs.minutes);
}

ostream& operator<< (ostream& out, const Date& d) {
	out << d.year << "-" << d.month << "-" << d.day;
	return out;
}

ostream& operator<< (ostream& out, const Time& t) {
	out << t.hours << ":" << t.minutes;
	return out;
}

istream& operator>>(istream& is, Time& t) {
	is >> t.hours;
	is.ignore(1);
	is >> t.minutes;

	return is;
}


istream& operator>>(istream& is, Date& d) {
	is >> d.year;
	is.ignore(1);

	is >> d.month;
	is.ignore(1);

	is >> d.day;

	return is;
}

/*
void UpdateTicket(AirlineTicket& ticket, const map<string, string>& updates) {
  map<string, string>::const_iterator it;

  it = updates.find("to");
  if (it != updates.end()) {
    ticket.to = it->second;
  }

  it = updates.find("from");
  if (it != updates.end()) {
    ticket.from = it->second;
  }

  it = updates.find("price");
  if (it != updates.end()) {
    istringstream is(it->second);
    is >> ticket.price;
  }
}

void UpdateTicketMacro(AirlineTicket& ticket, const map<string, string>& updates) {
  UPDATE_FIELD(ticket, to, updates);
  UPDATE_FIELD(ticket, from, updates);
  UPDATE_FIELD(ticket, price, updates);
  UPDATE_FIELD(ticket, airline, updates);
}
*/

/* авторское решение
#include "airline_ticket.h"
#include <tuple>
#include <iostream>
using namespace std;

bool operator == (const Date& lhs, const Date& rhs) {
  return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}

bool operator == (const Time& lhs, const Time& rhs) {
  return tie(lhs.hours, lhs.minutes) == tie(rhs.hours, rhs.minutes);
}

istream& operator>>(istream& is, Date& d) {
  is >> d.year;
  is.ignore(1);
  is >> d.month;
  is.ignore(1);
  is >> d.day;
  return is;
}

ostream& operator<<(ostream& os, const Date& d) {
  return os << d.year << '-' << d.month << '-' << d.day;
}

istream& operator>>(istream& is, Time& t) {
  is >> t.hours;
  is.ignore(1);
  is >> t.minutes;
  return is;
}

ostream& operator<<(ostream& os, const Time& t) {
  return os << t.hours << ':' << t.minutes;
}

#define UPDATE_FIELD(ticket, field, values) \
  {                                         \
    auto it = values.find(#field);          \
    if (it != values.end()) {               \
      istringstream is(it->second);         \
      is >> ticket.field;                   \
    }                                       \
  }
 */

