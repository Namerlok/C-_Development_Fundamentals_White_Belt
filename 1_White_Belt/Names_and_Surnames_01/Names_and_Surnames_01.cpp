#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Person {
public:
	void ChangeFirstName(int year, const string& first_name) {
		ch_name[year].first_name = first_name;
	}
	void ChangeLastName(int year, const string& last_name) {
		ch_name[year].last_name = last_name;
	}
	string GetFullName(int year) {
		string first_name = "", last_name = "";
		for (auto item: ch_name)
			if (item.first <= year) {
				if (item.second.first_name != "")
					first_name = item.second.first_name;
				if (item.second.last_name != "")
					last_name = item.second.last_name;
			}
		if (first_name == "" && last_name == "")
			return "Incognito";
		else if (first_name == "" && last_name != "")
			return last_name + " with unknown first name";
		else if (first_name != "" && last_name == "")
			return first_name + " with unknown last name";
		else
			return first_name + " " + last_name;
	}
private:
	struct name {
		string first_name = "";
		string last_name = "";
	};
	map<int, name> ch_name;
};

int main() {
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		cout << person.GetFullName(year) << endl;
	}

	return 0;
}
