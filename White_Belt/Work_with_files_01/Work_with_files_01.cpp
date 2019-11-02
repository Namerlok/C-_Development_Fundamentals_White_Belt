#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

	ifstream input("input.txt");

	if (!input.is_open()) {
		cout << "ERROR: open file!" << endl;
		return -1;
	}

	string str;
	while (getline(input, str)) {
		cout << str << endl;
	}

	return 0;
}
