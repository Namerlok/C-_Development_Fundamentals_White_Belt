#include <iostream>
#include <vector>
using namespace std;

int main() {

	vector<int> vec;
	int n;

	cin >> n;

	while (n > 0) {
		vec.insert(vec.begin(), n % 2);
		n /= 2;
	}

	for (auto i : vec) {
		cout << i;
	}

	return 0;
}
