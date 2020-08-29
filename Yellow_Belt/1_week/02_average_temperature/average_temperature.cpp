#include <iostream>
#include <vector>

using namespace std;

int main() {
	long long int n = 0;
	cin >> n;
	vector<long long int> temp(n);
	double sum = 0;

	for (int i = 0; i < n; i++) {
		cin >> temp[i];
		sum += temp[i];
	}
	sum /= n;
//	cout << sum << endl;
	long long int k = 0;
	vector<long long int> count;
	for (int i = 0; i < n; i++) {
		if (temp[i] > sum) {
			k++;
			count.push_back(i);
		}
	}
	cout << k << endl;
	for (int i: count)
		cout << i << " ";
	cout << endl;

	return 0;
}

