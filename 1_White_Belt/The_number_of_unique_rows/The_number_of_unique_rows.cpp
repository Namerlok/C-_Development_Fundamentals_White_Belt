#include <iostream>
#include <string>
#include <set>
using namespace std;

int main() {

	int n;
	cin >> n;
	set<string> str_un;

	for (int i = 0; i < n; i++) {
		string str;
		cin >> str;
		str_un.insert(str);
	}
	cout << str_un.size() << endl;

	return 0;
}
