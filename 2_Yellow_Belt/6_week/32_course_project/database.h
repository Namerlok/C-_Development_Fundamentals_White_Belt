/*
 * database.h
 *
 *  Created on: 4 сент. 2020 г.
 *      Author: Zarka
 */
#pragma once

#ifndef DATABASE_H_
#define DATABASE_H_

#include "date.h"
#include "test_runner.h"
#include "condition_parser.h"

#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <istream>
#include <ostream>
#include <utility>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Database {
public:
	void Add(const Date& date, const string& event);

	void Print(ostream& out) const;

	template <typename Predicate>
	int RemoveIf(const Predicate& predicate) {
/*
		int count_ = 0;
		for(auto& pair_ : storage) {
			const auto border = stable_partition(pair_.second.begin(), pair_.second.end(),
							[predicate, pair_](const auto& item) {
								return predicate(pair_.first, item);
							});
			if (border == pair_.second.begin()) {
				count_ = pair_.second.end() - pair_.second.begin();
				Date date_del = pair_.first;
				storage.erase(date_del);
			} else {
				for (int i = 0; i <= pair_.second.end() - border; ++i) {
					pair_.second.pop_back();
					++count_;
				}
			}
		}
		return count_;
*/

		int result = 0;

		map<Date, vector<string>> new_storage;
		map<Date, unordered_set<string>> new_checker;

		for (auto& pair_ : storage) {
			const auto border = stable_partition(pair_.second.begin(), pair_.second.end(),
					[predicate, pair_](const auto& item) {
						return predicate(pair_.first, item);
					});

			const size_t tmp = pair_.second.size();

			if (border == pair_.second.end()) {
				result += tmp;
			} else {
				new_storage[pair_.first] = vector<string>(border, pair_.second.end());
				new_checker[pair_.first] = unordered_set<string>(border, pair_.second.end());

				result += tmp - new_storage.at(pair_.first).size();
			}
		}

		storage = new_storage;
		checker = new_checker;

		return result;

	}

	template <typename Predicate>
	vector<pair<Date, string>> FindIf(const Predicate& predicate) const {

		vector<pair<Date, string>> out;

		for(auto& pair_ : storage) {
			vector<string> events;
			copy_if(pair_.second.begin(), pair_.second.end(), back_inserter(events),
					[predicate, pair_](const auto& item) {
						return predicate(pair_.first, item);
					});
			for(const string& event : events)
				out.push_back(make_pair(pair_.first, event));
		}
		return out;

		/*
		map<Date, vector<string>> tmp;
		vector<pair<Date, string>> result;

		for (const auto& pair_ : storage) {
			vector<string> tmp_vec;

			copy_if(pair_.second.begin(), pair_.second.end(), back_inserter(tmp_vec),
					[predicate, pair_](const auto& item) {
						return predicate(pair_.first, item);
					});

			if (tmp_vec.size() != 0) {
				tmp[pair_.first] = tmp_vec;
			}
		}

		for (const auto& pair_ : tmp) {
			for (const string& item : pair_.second) {
				result.push_back(make_pair(pair_.first, item));
			}
		}

		return result;
		*/
	}

	pair<Date, string> Last(const Date& date) const;

private:
	friend void TestDatabase();
	string UnitingDate(const Date& date) const;

	map<Date, vector<string>> storage;
	map<Date, unordered_set<string>> checker;
};

void TestDatabase();


ostream& operator<<(ostream& out, const pair<const Date, const vector<string>>& pair_);

ostream& operator<<(ostream& out, const pair<const Date, const string>& pair_);

bool operator==(const pair<const Date, const string>& pair_1, const pair<const Date, const string>& pair_2);

bool operator!=(const pair<const Date, const string>& pair_1, const pair<const Date, const string>& pair_2);

#endif /* DATABASE_H_ */


/* авторское решение
#pragma once

#include "date.h"
#include "event_set.h"

#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Entry {
  Date date;
  string event;
};

ostream& operator << (ostream& os, const Entry& e);
bool operator == (const Entry& lhs, const Entry& rhs);

class Database {
public:
  void Add(const Date& date, const string& event);

  template <typename Predicate>
  int RemoveIf(Predicate predicate) {
    int result = 0;
    for (auto& kv : data_) {
      const Date& date = kv.first;
      result += kv.second.RemoveIf([=](const string& event) {
        return predicate(date, event);
      });
    }
    for (auto it = data_.begin(); it != data_.end(); ) {
      if (it->second.GetAll().empty()) {
        data_.erase(it++);
      } else {
        ++it;
      }
    }
    return result;
  }

  template <typename Predicate>
  vector<Entry> FindIf(Predicate predicate) const {
    vector<Entry> result;
    for (auto& kv : data_) {
      for (const auto& event : kv.second.GetAll()) {
        if (predicate(kv.first, event)) {
          result.push_back(Entry{kv.first, event});
        }
      }
    }
    return result;
  }

  void Print(ostream& os) const;

  // throws invalid_argument if there is no last event for the given date
  Entry Last(const Date& date) const;

private:
  map<Date, EventSet> data_;
};

// Tests
void TestDatabaseAddAndPrint();
void TestDatabaseFind();
void TestDatabaseRemove();
void TestDatabaseLast();
 */

