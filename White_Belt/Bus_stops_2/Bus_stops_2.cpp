#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main() {

	int n;
	cin >> n;
	map<vector<string>, int> timetable;

	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;
		vector<string> ti_ta;
		for (int t = 0; t < k; t++) {
			string str;
			cin >> str;
			ti_ta.push_back(str);
		}
		bool ch = 0;
		for (const auto& t : timetable) {
			if (ti_ta == t.first) {
				cout << "Already exists for " << t.second << endl;
				ch = 1;
				break;
			}
		}
		if (ch == 0) {
			int size = (int)timetable.size() + 1;
			timetable[ti_ta] = size;
			cout << "New bus " << size << endl;
		}
	}

	return 0;
}
