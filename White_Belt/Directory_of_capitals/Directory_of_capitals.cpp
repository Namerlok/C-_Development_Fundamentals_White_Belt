#include <iostream>
#include <string>
#include <map>
using namespace std;

void print_DUMP (const map<string, string> &m);
bool chek(const string &str, const map<string, string> &countries);
void rename_map(const string &old_name, const string &new_name, map<string, string> &countries);

int main() {

	int n, i;
	string command, country1, country2, capital;
	map<string, string> countries;
	cin >> n;

	for (i = 0; i < n; i++) {

		cin >> command;

		if (command == "CHANGE_CAPITAL") {
			cin >> country1 >> capital;
			if (!chek(country1, countries)) {
				cout << "Introduce new country " << country1 << " with capital " << capital << endl;
				countries[country1] = capital;
			} else if (countries[country1] == capital) {
				cout << "Country " << country1 << " hasn't changed its capital" << endl;
			} else {
				cout << "Country " << country1 <<  " has changed its capital from " << countries[country1] << " to " << capital << endl;
				countries[country1] = capital;
			}
		} else if (command == "RENAME") {
			cin >> country1 >> country2;
			if (country1 == country2 || !chek(country1, countries) || chek(country2, countries))
				cout << "Incorrect rename, skip" << endl;
			else {
				cout << "Country " << country1 << " with capital " << countries[country1] << " has been renamed to " << country2 << endl;
				rename_map(country1, country2, countries);
			}
		} else if (command == "ABOUT") {
			cin >> country1;
			if (chek(country1, countries))
				cout << "Country " << country1 << " has capital " << countries[country1] << endl;
			else
				cout << "Country " << country1 <<" doesn't exist" << endl;
		} else if (command == "DUMP") {
			if (!countries.size())
				cout << "There are no countries in the world" << endl;
			else
				print_DUMP (countries);
		} else {
			cout << "ERROR!!! Unidentified command!!!" << endl;
		}
	}

	return 0;
}


void print_DUMP (const map<string, string> &countries) {

	for (const auto &item : countries)
		cout << item.first << "/" << item.second << " ";
	cout << endl;
}

bool chek(const string &str, const map<string, string> &countries) {

	for (const auto &item : countries)
		if (item.first == str)
			return true;
	return false;
}

void rename_map(const string &old_name, const string &new_name, map<string, string> &countries) {
	countries[new_name] = countries[old_name];
	countries.erase(old_name);
}

