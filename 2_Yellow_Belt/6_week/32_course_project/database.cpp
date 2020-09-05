/*
 * database.cpp
 *
 *  Created on: 4 сент. 2020 г.
 *      Author: Zarka
 */

#include "database.h"

void Database::Add(const Date& date, const string& event) {
	uint64_t count_ = checker[date].size();

	checker[date].insert(event);
	if (count_ < checker[date].size())
		storage[date].push_back(event);
}

void Database::Print(ostream& out) const {
	for(const auto& pair_date_event : storage)
		for(const auto& event : pair_date_event.second)
			out << pair_date_event.first << " " << event << endl;
}

pair<Date, string> Database::Last(const Date& date) const {

	if (storage.empty())
		throw invalid_argument("Empty storage");

	auto it = storage.upper_bound(date);

    if (it == storage.begin())
		throw invalid_argument("Less date");

    --it;

    return make_pair(it->first, it->second.back());
}

string Database::UnitingDate(const Date& date) const {
	string str_date;
	const int year = date.GetYear();
	const int month = date.GetMonth();
	const int day = date.GetDay();

	if (year < 10) {
		str_date += "000" + to_string(year) + "-";
	} else if (year < 100) {
		str_date += "00" + to_string(year) + "-";
	} else if (year < 1000) {
		str_date += "0" + to_string(year) + "-";
	} else {
		str_date += to_string(year) + "-";
	}

	if (month < 10) {
		str_date += "0" + to_string(month) + "-";
	} else {
		str_date += to_string(month) + "-";
	}

	if (day < 10) {
		str_date += "0" + to_string(day);
	} else {
		str_date += to_string(day);
	}

	return str_date;
}

ostream& operator<<(ostream& out, const pair<const Date, const vector<string>>& pair_) {
	for (const string& event: pair_.second) {
		out << pair_.first << " " << event;
	}
	return out;
}
ostream& operator<<(ostream& out, const pair<const Date, const string>& pair_) {
	out << pair_.first << " " << pair_.second;
	return out;
}

bool operator==(const pair<const Date, const string>& pair_1, const pair<const Date, const string>& pair_2) {
	return (pair_1.first == pair_2.first) && (pair_1.second == pair_2.second);
}

bool operator!=(const pair<const Date, const string>& pair_1, const pair<const Date, const string>& pair_2) {
	return !(pair_1 == pair_2);
}

/* авторское решение
#include "database.h"
#include <algorithm>
#include <stdexcept>
#include <tuple>
using namespace std;

void Database::Add(const Date& date, const string& event) {
  data_[date].Add(event);
}

void Database::Print(ostream& os) const {
  for (const auto& kv : data_) {
    for (const auto& event : kv.second.GetAll()) {
      os << kv.first << ' ' << event << endl;
    }
  }
}

Entry Database::Last(const Date& date) const {
  auto it = data_.upper_bound(date);
  if (it == data_.begin()) {
    throw invalid_argument("");
  }
  --it;
  return {it->first, it->second.GetAll().back()};
}

ostream& operator << (ostream& os, const Entry& e) {
  return os << e.date << " " << e.event;
}

bool operator == (const Entry& lhs, const Entry& rhs) {
  return tie(lhs.date, lhs.event) == tie(rhs.date, rhs.event);
}
 */

