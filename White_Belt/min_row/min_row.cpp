#include <iostream>
#include <string>
using namespace std;

int main() {

	string str1, str2, str3;

	cin >> str1 >> str2 >> str3;

	if (str1 <= str2 && str1 <= str3)
		cout << str1;
	else if (str2 <= str1 && str2 <= str3)
		cout << str2;
	else if (str3 <= str1 && str3 <= str2)
			cout << str3;

	return 0;
}
