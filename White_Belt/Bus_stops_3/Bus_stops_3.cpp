#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;

int main() {
	int n;
	cin >> n;

	map<set<string>, int> timetable;

	for (; n > 0; n--) {
		int i;
		cin >> i;

		set<string> stops;
		for (; i > 0; i--) {
			string stop;
			cin >> stop;
			stops.insert(stop);
		}
		if (timetable.count(stops) == 0) {
			const int size = timetable.size() + 1;
			timetable[stops] = size;
			cout << "New bus " << size << endl;
		} else {
			cout << "Already exists for " << timetable[stops] << endl;
		}
	}

	return 0;
}
