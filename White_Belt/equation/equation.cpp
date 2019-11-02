#include <iostream>
#include <cmath>
using namespace std;

int main() {

	double a, b, c;

	cin >> a >> b >> c;

	if (a == 0.0) {
		if (b != 0.0)
			cout << -c / b;
	} else {
		double d = b * b - 4.0 * a * c;

		if (d == 0.0)
			cout << -b / (2 * a);
		else if (d > 0) {
			double sqrt_d = sqrt (d);

			cout << (-b - sqrt_d) / (2 * a) << " " << (-b + sqrt_d) / (2 * a);
		}
	}

	return 0;
}
