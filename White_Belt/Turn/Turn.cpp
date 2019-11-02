#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {

	int N, a, i, j, summ;
	string str;
	vector<string> v;
	cin >> N;
//	cout << "N = " << N << endl;

	for (i = 0; i < N; i++) {

//		cout << "i = " <<i << endl;
		cin >> str;

		if (str == "COME") {
			cin >> a;
			j = (int)v.size();
			v.resize (v.size() + a);
			for ( ; j < (int)v.size(); j++ )
				v[j] = "QUIET";
		} else if (str == "WORRY") {
			cin >> a;
			v[a] = "WORRY";
		} else if (str == "QUIET") {
			cin >> a;
			v[a] = "QUIET";
		} else if (str == "WORRY_COUNT") {
			summ = 0;
			for (j = 0; j < (int)v.size(); j++) {
				if (v[j] == "WORRY") {
					summ++;
				}
			}
			cout << summ << endl;
		} else {
			cout << "EROOR" << endl;
		}
	}

	return 0;
}

/*
 *
8
COME 5
WORRY 1
WORRY 4
COME -2
WORRY_COUNT
COME 3
WORRY 3
WORRY_COUNT
 *
 */
