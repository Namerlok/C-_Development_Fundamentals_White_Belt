#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {

	ifstream input("input.txt");

	if (!input.is_open()) {
		cout << "ERROR: open file \"input.txt\"\n";
		return -1;
	}

	double n;
	cout << fixed << setprecision(3);
	while (input >> n) {
		cout << n << endl;
	}

	return 0;
}
