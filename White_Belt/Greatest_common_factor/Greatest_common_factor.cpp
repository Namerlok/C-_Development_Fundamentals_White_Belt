#include <iostream>
using namespace std;

int main() {

	int swap, a, b;

	cin >> a >> b;

	if (a < b) {
		swap = a;
		a = b;
		b = swap;
	}

	while (b != 0) {
		swap = b;
		b = a % b;
		a = swap;
	}
	cout << a << endl;

	return 0;
}
