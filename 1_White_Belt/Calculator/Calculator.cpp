#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>

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
    	if (new_denominator == 0) {
    		throw invalid_argument("EROOR: denominator == 0");
    	}
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
	if (fraction2.Numerator() == 0)
		throw domain_error("EROOR: division by zero");
	return Rational (fraction1.Numerator() * fraction2.Denominator(),
					 fraction1.Denominator() * fraction2.Numerator());
}

istringstream& operator>> (istringstream& input, Rational& fraction) {
	int p = 0, q = 1;
	if (!(input >> p))
		return input;
	input.ignore(1);
	if (!(input >> q))
		return input;
	fraction = {p, q};
	return input;
}

ostream& operator<< (ostream& output, const Rational& fraction) {
	output << fraction.Numerator() << "/" << fraction.Denominator();
	return output;
}

bool operator< (const Rational& fraction1, const Rational& fraction2) {
	return (fraction1.Numerator() * fraction2.Denominator() < fraction2.Numerator() * fraction1.Denominator());
}

bool operator> (const Rational& fraction1, const Rational& fraction2) {
	return (fraction1.Numerator() * fraction2.Denominator() > fraction2.Numerator() * fraction1.Denominator());
}

bool operator!= (const Rational& fraction1, const Rational& fraction2) {
	return (fraction1.Numerator() != fraction2.Numerator()) &&
		   (fraction1.Denominator() != fraction2.Denominator());
}

int main () {

	int p = 0, q = 1;
	char c;

	cin >> p >> c >> q;
	if (c != '/') {
		cout << "Invalid argument";
		return 1;
	}

	Rational r1;
    try {
        r1 = {p, q};
    } catch (invalid_argument&) {
    	cout << "Invalid argument";
		return 2;
    }

    char operation;
    cin >> operation;

    cin >> p >> c >> q;
	if (c != '/') {
		cout << "Invalid argument";
		return 3;
	}

	Rational r2;
	try {
		r2 = {p, q};
	} catch (invalid_argument&) {
		cout << "Invalid argument";
		return 4;
	}

	try {
		if (operation == '+') {
			cout << r1 + r2;
		} else if (operation == '-') {
			cout << r1 - r2;
		} else if (operation == '*') {
			cout << r1 * r2;
		} else {
			cout << r1 / r2;
		}

	} catch (domain_error&) {
		cout << "Division by zero";
		return 5;
    }

    return 0;
}
