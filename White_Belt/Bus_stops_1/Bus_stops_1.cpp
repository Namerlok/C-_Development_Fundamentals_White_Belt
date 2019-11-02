#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

//stop_search
vector<string> bus_search (const string& stop, const map<string, vector<string>>& timetable);
void print_vec_str (const vector<string>& buses, const vector<string>& bb);
void del_elem_vec_value (const string& bus, vector<string>& buses);

int main() {

	map<string, vector<string>> timetable;
	vector<string> bb;
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		string command, bus, stop;
		cin >> command;

		if (command == "NEW_BUS") {
			int k;
			cin >> bus >> k;

			bb.push_back(bus);
			for (int j = 0; j < k; j++) {
				cin >> stop;
				timetable[bus].push_back(stop);
			}
		} else if (command == "BUSES_FOR_STOP") {
			cin >> stop;
			vector<string> buses = bus_search (stop, timetable);
			if (buses.empty()) {
				cout << "No stop" << endl;
			} else {
				print_vec_str (buses, bb);
			}
		} else if (command == "STOPS_FOR_BUS") {
			cin >> bus;
			if (timetable.count(bus) != 0) {
				for (const auto& v : timetable[bus]) {
					cout << "Stop " << v << ": ";
					vector<string> buses = bus_search (v, timetable);
					del_elem_vec_value (bus, buses);
					if (buses.empty()) {
						cout << "no interchange" << endl;
					} else {
						print_vec_str (buses, bb);
					}
				}
			} else {
				cout << "No bus" << endl;
			}
		} else if (command == "ALL_BUSES") {
			if (timetable.size() == 0) {
				cout << "No buses" << endl;
			} else {
				for (const auto& k : timetable) {
					cout << "Bus " << k.first << ": ";
					for (const auto& i : k.second) {
						cout << i << " ";
					}
					cout << endl;
				}
			}
		}
	}

	return 0;
}

vector<string> bus_search (const string& stop, const map<string, vector<string>>& timetable) {

	vector<string> buses;
	for (const auto& k : timetable) {
		for (const auto& t : k.second) {
			if (t == stop) {
				buses.push_back(k.first);
				break;
			}
		}
	}

	return buses;
}

void print_vec_str (const vector<string>& buses, const vector<string>& bb) {
	for (const auto& i : bb) {
		for(const auto& k : buses) {
			if (i == k ) {
				cout << i << " ";
				break;
			}
		}
	}
	cout << endl;
}

void del_elem_vec_value (const string& bus, vector<string>& buses) {
	for (int i = 0; i < (int)buses.size(); i++) {
		if (buses[i] == bus) {
			buses.erase(buses.begin() + i);
			break;
		}
	}
}

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
