#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <locale>

using namespace std;

void print_vector (const vector<string>& v);

int main() {

	int n;
	cin >> n;

	vector<string> m(n);
	for (int i = 0; i < n; i++) {
		string str;
		cin >> str;
		m[i] = str;
	}

	sort (begin(m), end(m),
		[](const auto& s1, const auto& s2) {
			int i;
			for (i = 0; tolower (s1[i]) == tolower (s2[i]) && i < (int)s1.size() && i < (int)s2.size(); i++);
			return ((tolower (s1[i]) - tolower (s2[i]) < 0) ? true : false);
		}
	);

	print_vector (m);

	return 0;
}

void print_vector (const vector<string>& v) {
	for (const auto& i : v) {
		cout << i << " ";
	}
	cout << endl;
}
