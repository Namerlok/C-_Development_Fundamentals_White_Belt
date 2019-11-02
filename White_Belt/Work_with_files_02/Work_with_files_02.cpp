#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

	ifstream input("input.txt");
	ofstream output("output.txt");

	if (!input.is_open()) {
		cout << "ERROR: open file \"input.txt\"!" << endl;
		return -1;
	} else if (!output.is_open()) {
		cout << "ERROR: open file \"output.txt\"!" << endl;
		return -1;
	}

	string new_str, str = "";
	while (getline(input, new_str)) {
		str += new_str + '\n';
	}
	output << str;

	return 0;
}
