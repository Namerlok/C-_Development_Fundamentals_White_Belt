/*
 * bus_manager.h
 *
 *  Created on: 16 июл. 2020 г.
 *      Author: Zarka
 */
#pragma once

#ifndef BUS_MANAGER_H_
#define BUS_MANAGER_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "responses.h"

using namespace std;

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops);
  BusesForStopResponse GetBusesForStop(const string& stop) const;
  StopsForBusResponse GetStopsForBus(const string& bus) const;
  AllBusesResponse GetAllBuses() const;

private:
  map<string, vector<string>> buses_to_stops;
  map<string, vector<string>> stops_to_buses;
};

#endif /* BUS_MANAGER_H_ */

