#include <iostream>

using namespace std;

struct Incognizable {
	int a = 0;
	int b = 0;
};

int main() {
	Incognizable a;
	Incognizable b = {};
	Incognizable c = {0};
	Incognizable d = {0, 1};
	cout << a.a << a.b << endl;
	cout << b.a << b.b << endl;
	cout << c.a << c.b << endl;
	cout << d.a << d.b << endl;

	return 0;
}
