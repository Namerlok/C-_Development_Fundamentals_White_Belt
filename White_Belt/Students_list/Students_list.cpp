#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
struct person {
	string first_name;
	string second_name;
	long long int day;
	long long int month;
	long long int year;
};
*/

struct person {
  string name;
  string birthday;
};

int main () {

	int n = 0;
	cin >> n;

	vector<person> people;
	string first_name, second_name, day, month, year;

	for (int i = 0; i < n; i++) {
		cin >> first_name >> second_name >> day >> month >> year;
		people.push_back (person{first_name + " " + second_name, day + "." + month + "." + year});
	}

	string command = "";
	int number_st = 0;
	int m = 0;
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> command >> number_st;
		number_st--;
		if (command == "name" && number_st >= 0 && number_st < n) {
			cout << people[number_st].name << endl;
		} else if (command == "date" && number_st >= 0 && number_st < n) {
			cout << people[number_st].birthday << endl;
		} else {
			cout << "bad request" << endl;
		}
	}

	return 0;
}
