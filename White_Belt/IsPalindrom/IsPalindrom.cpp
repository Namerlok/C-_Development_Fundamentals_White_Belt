#include <iostream>
#include <string>
using namespace std;

bool IsPalindrom (string str) {


	for (int b = 0, e = str.size() - 1; b < e; b++, e-- ) {
//		cout << str[b] << " " << str[e] << endl;
		if ( str[b] != str[e] )
			return 0;
	}
	return 1;
}

int main () {

	string str;
	cin >> str;

	cout << IsPalindrom(str) << endl;

	return 0;
}
