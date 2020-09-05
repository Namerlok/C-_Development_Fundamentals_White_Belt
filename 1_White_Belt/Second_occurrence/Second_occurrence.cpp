#include <iostream>
#include <string>
using namespace std;

int main() {

	string str;
	int n = 0;
	cin >> str;

	for (int i = 0; i < (int)str.size(); i++) {
		if (str[i] == 'f')
			n++;
		if (n == 2) {
			cout << i << endl;
			break;
		}
	}
	if (n == 1)
		cout << -1 << endl;
	else if (n == 0)
		cout << -2 << endl;

	return 0;
}
