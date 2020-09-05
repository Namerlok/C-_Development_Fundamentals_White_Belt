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

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
//        if (v != (vector<Rational> {{1, 25}, {1, 2}, {3, 4}})) {
//            cout << "Rationals comparison works incorrectly" << endl;
//            return 2;
//        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
