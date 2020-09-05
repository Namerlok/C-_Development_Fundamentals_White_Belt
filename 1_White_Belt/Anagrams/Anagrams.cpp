#include <iostream>
#include <string>
#include <map>
using namespace std;

bool BuildCharCounters (const string& str1, const string& str2);
void print_map (const map<char, int> m);

int main() {

	int N, i;
	string str1, str2;

	cin >> N;

	for (i = 0; i < N; i++) {
		cin >> str2 >> str1;
		if (BuildCharCounters (str1, str2))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}

bool BuildCharCounters (const string& str1, const string& str2) {
	map<char, int> ch1, ch2;
	for (const auto& i : str1)
		++ch1[i];
	for (const auto& i : str2)
		++ch2[i];
//	print_map (ch1);
//	print_map (ch2);
	return (ch1 == ch2);
}

void print_map (const map<char, int> m) {

	cout << endl;
	for (const auto& item : m)
		cout << item.first << "	" << item.second << endl;
	cout << endl;
}

/*
3
eat tea
find search
master stream
 */
