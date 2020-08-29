#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

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

istream& operator >> (istream& is, Query& q) {
	string operation_code;
	is >> operation_code;
	if (operation_code == "NEW_BUS") {
		q.type = QueryType::NewBus;
		q.stops.clear();
		int stop_count;
		is >> q.bus >> stop_count;
		for (int i = 0; i < stop_count; ++i) {
			string stop;
			is >> stop;
			q.stops.push_back(stop);
		}
	} else if (operation_code == "BUSES_FOR_STOP") {
		q.type = QueryType::BusesForStop;
		is >> q.stop;
	} else if (operation_code == "STOPS_FOR_BUS") {
		q.type = QueryType::StopsForBus;
		is >> q.bus;
	} else if (operation_code == "ALL_BUSES") {
		q.type = QueryType::AllBuses;
	}
	return is;
}

struct BusesForStopResponse {
	int count_stop = 0;
	vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	if (r.count_stop == 0) {
		os << "No stop";
	} else {
		for (const string& bus: r.buses)
			os << bus << " ";
	}
	return os;
}

struct StopsForBusResponse {
	int count_stops;
	vector<string> stops;
	map<string, vector<string>> buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	if (r.count_stops == 0) {
		os << "No bus";
	} else {
		for (const auto& stop: r.stops) {
			os << "Stop " << stop << ": ";
			if (r.buses.at(stop).size() == 0) {
				os << "no interchange" << endl;
			} else {
				for (const string& bus: r.buses.at(stop))
					os << bus <<  " ";
				os << endl;
			}
		}
	}
	return os;
}

struct AllBusesResponse {
	bool no_buses = true;
	map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
	if (r.no_buses) {
		os << "No buses";
	} else {
		for (const auto& bus_item : r.buses_to_stops) {
			cout << "Bus " << bus_item.first << ": ";
			for (const string& stop : bus_item.second) {
				cout << stop << " ";
			}
			os << endl;
		}
	}
	return os;
}

class BusManager {
public:
	void AddBus(const string& bus, const vector<string>& stops) {
		buses_to_stops[bus] = stops;
		for (const string& stop: stops)
			stops_to_buses[stop].push_back(bus);
//		BusManagerPtintf();
	}

	BusesForStopResponse GetBusesForStop(const string& stop) const {
		BusesForStopResponse r;
		if ((r.count_stop = stops_to_buses.count(stop)) != 0)
			r.buses = stops_to_buses.at(stop);
		return r;
	}

	StopsForBusResponse GetStopsForBus(const string& bus) const {
		StopsForBusResponse r;
		if ((r.count_stops = buses_to_stops.count(bus)) != 0) {
	        for (const string& stop : buses_to_stops.at(bus)) {
	        	r.stops.push_back(stop);
	        	r.buses[stop];
	            for (const string& other_bus : stops_to_buses.at(stop)) {
					if (bus != other_bus) {
						r.buses[stop].push_back(other_bus);
					}
	            }
	        }
		}
		return r;
	}

	AllBusesResponse GetAllBuses() const {
		AllBusesResponse r;
		if (buses_to_stops.empty()) {
			r.no_buses = true;
		} else {
			r.no_buses = false;
			r.buses_to_stops = buses_to_stops;
		}
		return r;
	}

private:
	map<string, vector<string>> buses_to_stops, stops_to_buses;

	void BusManagerPtintf() const {
		cout << "------------------------------------------TEST------------------------------------------" << endl;
		cout << "buses_to_stops: " << endl;
		for (const auto& bus: buses_to_stops) {
			cout << "\t" << bus.first << ":" << endl << "\t\t";
			for (const string& stop: bus.second)
				cout << stop << " ";
			cout << endl;
		}
		cout << "stops_to_buses: " << endl;
		for (const auto& bus: stops_to_buses) {
			cout << "\t" << bus.first << ":" << endl << "\t\t";
			for (const string& stop: bus.second)
				cout << stop << " ";
			cout << endl;
		}
		cout << "----------------------------------------END TEST----------------------------------------" << endl;
	}
};

// Ќе мен¤¤ тела функции main, реализуйте функции и классы выше

int main() {
	int query_count;
	Query q;

	cin >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i) {
		cin >> q;
		switch (q.type) {
		case QueryType::NewBus:
			bm.AddBus(q.bus, q.stops);
			break;
		case QueryType::BusesForStop:
			cout << bm.GetBusesForStop(q.stop) << endl;
			break;
		case QueryType::StopsForBus:
			cout << bm.GetStopsForBus(q.bus) << endl;
			break;
		case QueryType::AllBuses:
			cout << bm.GetAllBuses() << endl;
			break;
		}
	}

	return 0;
}

/*
int main() {
  int q;
  cin >> q;

  map<string, vector<string>> buses_to_stops, stops_to_buses;

  for (int i = 0; i < q; ++i) {
    string operation_code;
    cin >> operation_code;

    if (operation_code == "NEW_BUS") {

      string bus;
      cin >> bus;
      int stop_count;
      cin >> stop_count;
      vector<string>& stops = buses_to_stops[bus];
      stops.resize(stop_count);
      for (string& stop : stops) {
        cin >> stop;
        stops_to_buses[stop].push_back(bus);
      }

    } else if (operation_code == "BUSES_FOR_STOP") {

      string stop;
      cin >> stop;
      if (stops_to_buses.count(stop) == 0) {
        cout << "No stop" << endl;
      } else {
        for (const string& bus : stops_to_buses[stop]) {
          cout << bus << " ";
        }
        cout << endl;
      }

    } else if (operation_code == "STOPS_FOR_BUS") {

      string bus;
      cin >> bus;
      if (buses_to_stops.count(bus) == 0) {
        cout << "No bus" << endl;
      } else {
        for (const string& stop : buses_to_stops[bus]) {
          cout << "Stop " << stop << ": ";
          if (stops_to_buses[stop].size() == 1) {
            cout << "no interchange";
          } else {
            for (const string& other_bus : stops_to_buses[stop]) {
              if (bus != other_bus) {
                cout << other_bus << " ";
              }
            }
          }
          cout << endl;
        }
      }

    } else if (operation_code == "ALL_BUSES") {

      if (buses_to_stops.empty()) {
        cout << "No buses" << endl;
      } else {
        for (const auto& bus_item : buses_to_stops) {
          cout << "Bus " << bus_item.first << ": ";
          for (const string& stop : bus_item.second) {
            cout << stop << " ";
          }
          cout << endl;
        }
      }

    }
  }

  return 0;
}
*/

/*
10
ALL_BUSES
BUSES_FOR_STOP Marushkino
STOPS_FOR_BUS 32K
NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo
NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo
BUSES_FOR_STOP Vnukovo
NEW_BUS 950 6 Kokoshkino Marushkino Vnukovo Peredelkino Solntsevo Troparyovo
NEW_BUS 272 4 Vnukovo Moskovsky Rumyantsevo Troparyovo
STOPS_FOR_BUS 272
ALL_BUSES
*/

/* јвторское решение
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

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

istream& operator >> (istream& is, Query& q) {
  string typeStr;
  is >> typeStr;
  if (typeStr == "NEW_BUS") {
    q.type = QueryType::NewBus;
    is >> q.bus;
    int stop_count = 0;
    is >> stop_count;
    q.stops.resize(stop_count);
    for (auto& stop : q.stops) {
      is >> stop;
    }
  } else if (typeStr == "BUSES_FOR_STOP") {
    q.type = QueryType::BusesForStop;
    is >> q.stop;
  } else if (typeStr == "STOPS_FOR_BUS") {
    q.type = QueryType::StopsForBus;
    is >> q.bus;
  } else if (typeStr == "ALL_BUSES") {
    q.type = QueryType::AllBuses;
  }

  return is;
}

struct BusesForStopResponse {
  vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
  if (r.buses.empty()) {
    os << "No stop";
  } else {
    for (const auto& bus : r.buses) {
      os << bus << " ";
    }
  }
  return os;
}

struct StopsForBusResponse {
  string bus;
  vector<pair<string, vector<string>>> stops_for_buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
  if (r.stops_for_buses.empty()) {
    os << "No bus";
  } else {
    bool first = true;
    for (const auto& stop_and_buses : r.stops_for_buses) {
      if (!first) {
        os << endl;
      }
      first = false;
      os << "Stop " << stop_and_buses.first << ":";
      if (stop_and_buses.second.size() == 1) {
        os << " no interchange";
      } else {
        for (const auto& bus : stop_and_buses.second) {
          if (bus != r.bus) {
            os << " " << bus;
          }
        }
      }
    }
  }
  return os;
}

struct AllBusesResponse {
  map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
  if (r.buses_to_stops.empty()) {
    os << "No buses";
  } else {
    bool first = true;
    for (const auto& bus_and_stops : r.buses_to_stops) {
      if (!first) {
        os << endl;
      }
      first = false;
      os << "Bus " << bus_and_stops.first << ":";
      for (const auto& stop : bus_and_stops.second) {
        os << " " << stop;
      }
    }
  }
  return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops.insert(make_pair(bus, stops));
    for (const auto& stop : stops) {
      stops_to_buses[stop].push_back(bus);
    }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
    if (stops_to_buses.count(stop) == 0) {
      return BusesForStopResponse{vector<string>()};
    } else {
      return BusesForStopResponse{stops_to_buses.at(stop)};
    }
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
    vector<pair<string, vector<string>>> result;

    if (buses_to_stops.count(bus) > 0) {
      for (const auto& stop : buses_to_stops.at(bus)) {
        result.push_back(make_pair(stop, stops_to_buses.at(stop)));
      }
    }
    return StopsForBusResponse{bus, result};
  }

  AllBusesResponse GetAllBuses() const {
    return AllBusesResponse{buses_to_stops};
  }

private:
  map<string, vector<string>> buses_to_stops;
  map<string, vector<string>> stops_to_buses;
};
 */


