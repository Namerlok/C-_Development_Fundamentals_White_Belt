#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> PalindromFilter (vector<string> words, int minLength) {
	vector<string> write;
	int b, e;
//	cout << "Hi_2" << endl;
//	for (auto x : words) {
//			cout << x << " ";
//	}

	for (auto i : words) {
//		cout << i.size() << endl;
		for (b = 0, e = i.size() - 1; b < e; b++, e-- ) {
//			cout << i[b] << " " << i[e] << endl;
			if (i[b] != i[e]) {
				break;
			}
		}
		if (b >= e && (int)i.size() >= minLength) {
			write.push_back(i);
		}
	}

	return write;
}

int main() {

	int n;
	int minLength;
	cin >> n >> minLength;

	vector<string> words(n);

	for (string &i : words) {
		cin >> i;
	}

	cout << "Hi_1" << endl;
	vector<string> word = PalindromFilter(words, minLength);
	cout << "Hi_3" << endl;
	for (auto x : word) {
		cout << x << " ";
	}

	return 0;
}
