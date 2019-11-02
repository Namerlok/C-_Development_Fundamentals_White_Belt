#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define NUMBER_OF_MONTHS 12

void print_vec (const vector<string> &m) {

	for (auto i : m)
		cout << i << " ";
	cout << endl;
}

int main() {

	int N, i, numb_m = 0, j, k, L;
	vector<int> month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	vector<vector<string>> m(month[numb_m]);
	string str;

	cin >> N;
	for (i = 0; i < N; i++) {

//		cout << "i = " << i << endl;
		cin >> str;
		if (str == "ADD") {
			cin >> j >> str;
			m[j - 1].push_back(str);
		} else if (str == "DUMP") {
			cin >> j;
			cout << m[j - 1].size() << " ";
			print_vec (m[j - 1]);
		} else if (str == "NEXT") {
			j = month[(numb_m + 1) % NUMBER_OF_MONTHS];
			k = month[numb_m % NUMBER_OF_MONTHS];
			if (j - k >= 0) {
				m.resize(j);
				for ( L = k; L < j; L++ )
					m[L].clear();
			} else {
				for (L = 0; L < k - j; L++){
					m[j - 1].insert(end(m[j - 1]), begin(m[k - 1 - L]), end(m[k - 1 - L]));
				}
			}
			numb_m++;
		}
	}


	return 0;
}

/*
12
ADD 5 Salary
ADD 31 Walk
ADD 30 WalkPreparations
NEXT
DUMP 5
DUMP 28
NEXT
DUMP 31
DUMP 30
DUMP 28
ADD 28 Payment
DUMP 28
*/
