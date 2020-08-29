/*
 * query.h
 *
 *  Created on: 16 θώλ. 2020 γ.
 *      Author: Zarka
 */

/*
 *	enum class QueryType
 *	struct Query
 *	ξαϊβλενθε istream& operator >> (istream& is, Query& q)
 */

#pragma once

#ifndef QUERY_H_
#define QUERY_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q);

#endif /* QUERY_H_ */

