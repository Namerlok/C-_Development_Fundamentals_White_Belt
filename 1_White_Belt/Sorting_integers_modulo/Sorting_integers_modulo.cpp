#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void print_vector (const vector<int>& v);

int main() {

	vector<int> m;

	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		m.push_back(t);
	}
	sort (begin(m), end(m), [](int x, int y) {return ((abs (x) < abs (y)) ? true : false);});

	print_vector (m);

	return 0;
}

void print_vector (const vector<int>& v) {
	for (const auto& i : v) {
		cout << i << " ";
	}
	cout << endl;
}
