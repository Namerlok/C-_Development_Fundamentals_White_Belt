#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

int main() {

	ifstream input("input.txt");

	if (!input.is_open()) {
		cout << "ERROR: open file \"inpur.txt\"\n";
		return -1;
	}

	int height = 0,	width = 0;
	input >> height >> width;
	int size = height * width;
	vector<int> numbers(size);


	for (int i = 0, n = 0; i < size; i++) {
		input >> n;
		numbers[i] = n;
		if ((i + 1) % width != 0)
			input.ignore(1);
	}

	for (int i = 0; i < size; i++) {
		cout << setw(10) << numbers[i];
		if ((i + 1) % width != 0)
			cout << " ";
		else if ((i + 1) % width == 0 && i + 1 != size)
			cout << endl;
	}

	return 0;
}
