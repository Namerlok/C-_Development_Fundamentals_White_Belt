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

Rational operator+ (const Rational& fraction1, const Rational& fraction2) {
	return Rational (fraction1.Numerator() * fraction2.Denominator() + fraction2.Numerator() * fraction1.Denominator(),
					 fraction1.Denominator() * fraction2.Denominator());
}

Rational operator- (const Rational& fraction1, const Rational& fraction2) {
	return Rational (fraction1.Numerator() * fraction2.Denominator() - fraction2.Numerator() * fraction1.Denominator(),
					 fraction1.Denominator() * fraction2.Denominator());
}

bool operator== (const Rational& fraction1, const Rational& fraction2) {
	return (fraction1.Numerator() == fraction2.Numerator()) &&
		   (fraction1.Denominator() == fraction2.Denominator());
}

Rational operator* (const Rational& fraction1, const Rational& fraction2) {
	return Rational (fraction1.Numerator() * fraction2.Numerator(),
					 fraction1.Denominator() * fraction2.Denominator());
}

Rational operator/ (const Rational& fraction1, const Rational& fraction2) {
	return Rational (fraction1.Numerator() * fraction2.Denominator(),
					 fraction1.Denominator() * fraction2.Numerator());
}

int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}

