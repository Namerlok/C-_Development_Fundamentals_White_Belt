/*
 * responses.h
 *
 *  Created on: 16 июл. 2020 г.
 *      Author: Zarka
 */
/*
 * struct BusesForStopResponse
 * ostream& operator << (ostream& os, const BusesForStopResponse& r)
 * struct StopsForBusResponse
 * ostream& operator << (ostream& os, const StopsForBusResponse& r)
 * struct AllBusesResponse
 * ostream& operator << (ostream& os, const AllBusesResponse& r)
 */

#pragma once

#ifndef RESPONSES_H_
#define RESPONSES_H_

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct BusesForStopResponse {
  vector<string> buses;
};

struct StopsForBusResponse {
  string bus;
  vector<pair<string, vector<string>>> stops_for_buses;
};

struct AllBusesResponse {
  map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);
ostream& operator << (ostream& os, const StopsForBusResponse& r);
ostream& operator << (ostream& os, const AllBusesResponse& r);

#endif /* RESPONSES_H_ */

