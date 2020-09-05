#include <iostream>
#include <fstream>
#include <sstream>

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

int main() {
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 4;
        }
    }

    cout << "OK" << endl;
    return 0;
}

