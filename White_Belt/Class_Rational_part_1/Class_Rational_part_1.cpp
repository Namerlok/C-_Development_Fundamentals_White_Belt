#include <iostream>
using namespace std;

class Rational {
public:
    Rational () {
    	if (numerator == 0) {
    		denominator = 1;
    	} else if (denominator < 0) {
			numerator = -numerator;
			denominator = -denominator;
		}
    }

    Rational (int new_numerator, int new_denominator) {
    	if (new_numerator == 0) {
    		numerator = 0;
    		denominator = 1;
    	} else if (new_denominator < 0) {
    		numerator = -new_numerator;
    		denominator = -new_denominator;
    	} else {
    		numerator = new_numerator;
    		denominator = new_denominator;
    	}
    }

    int Numerator () const {
        return numerator / NOD (numerator, denominator);
    }

    int Denominator () const {
        return denominator / NOD (numerator, denominator);
    }

private:
    int numerator = 0;
	int denominator = 1; // всегда > 0

	int NOD (int num1, int nim2) const {
		int swap;

		if (num1 < nim2) {
			swap = num1;
			num1 = nim2;
			nim2 = swap;
		}

		while (nim2 != 0) {
			swap = nim2;
			nim2 = num1 % nim2;
			num1 = swap;
		}

		return (num1 >= 0) ? num1 : -num1;
	}
};

int main() {
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    {
		const Rational r = {10, -6};
		if (r.Numerator() != -5 || r.Denominator() != 3) {
			cout << "(Rational = {10, -6}) != -5/3" << endl;
			return 6;
		}
	}

    {
		const Rational r(-4, -6);
		if (r.Numerator() != 2 || r.Denominator() != 3) {
			cout << "Rational(4, 6) != 2/3" << endl;
			return 7;
		}
	}

    {
		const Rational r = {-10, -6};
		if (r.Numerator() != 5 || r.Denominator() != 3) {
			cout << "(Rational = {-10, -6}) != 5/3" << endl;
			return 8;
		}
	}

    {
		const Rational r(0, 6);
		if (r.Numerator() != 0 || r.Denominator() != 1) {
			cout << "Rational(0, 6) != 0/1" << endl;
			return 9;
		}
	}

    {
		const Rational r(-1, 1);
		if (r.Numerator() != -1 || r.Denominator() != 1) {
			cout << "Rational(-1, 1) != -1/1" << endl;
			return 10;
		}
	}

    cout << "OK" << endl;
/*
    int p = 0, q = 1;

    cin >> p >> q;

    const Rational r(p,q);
    cout << r.Numerator() << " " << r.Denominator() << endl;
*/
    return 0;
}
