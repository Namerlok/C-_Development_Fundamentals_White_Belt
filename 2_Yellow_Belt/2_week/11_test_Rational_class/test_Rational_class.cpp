#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw runtime_error(os.str());
	}
}

void Assert(bool b, const string& hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
		try {
			func();
			cerr << test_name << " OK" << endl;
		} catch (exception& e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		} catch (...) {
			++fail_count;
			cerr << "Unknown exception caught" << endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};


class Rational {
public:
  // Вы можете вставлять сюда различные реализации,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный

	Rational() {
		NUMERATOR = 0;
		DENOMINATOR = 1;
	}
	Rational(int numerator, int denominator) {
		NUMERATOR = numerator;
		DENOMINATOR = denominator;



		for (int i = 2; i <= abs(numerator) && i <= abs(denominator); ++i) {
			if (abs(numerator) % i == 0 && abs(denominator) % i == 0) {
				NUMERATOR /= i;
				DENOMINATOR /= i;
			}
		}

		if (NUMERATOR * DENOMINATOR < 0) {
			NUMERATOR = -abs(NUMERATOR);
			DENOMINATOR = abs(DENOMINATOR);
		} else if (NUMERATOR * DENOMINATOR > 0) {
			NUMERATOR = abs(NUMERATOR);
			DENOMINATOR = abs(DENOMINATOR);
		} else if (NUMERATOR== 0) {
			DENOMINATOR = 1;
		}
	}

	int Numerator() const {
		return NUMERATOR;
	}

	int Denominator() const {
		return DENOMINATOR;
	}
private:
	int NUMERATOR;
	int DENOMINATOR;
};


void TestConstructor() {
	Rational test1;
	AssertEqual(test1.Numerator(), 0, "конструктор по умолчанию (числитель)");
	AssertEqual(test1.Denominator(), 1, "конструктор по умолчанию (знаменатель)");

	Rational test2(6, 3);
	AssertEqual(test2.Numerator(), 2, "заданный конструктор (числитель)");
	AssertEqual(test2.Denominator(), 1, "заданный конструктор (знаменатель)");

	Rational test3(10, 15);
	AssertEqual(test3.Numerator(), 2, "заданный конструктор (числитель)");
	AssertEqual(test3.Denominator(), 3, "заданный конструктор (знаменатель)");

	Rational test4(0, 3);
	AssertEqual(test4.Numerator(), 0, "заданный конструктор с 0 числителем (числитель)");
	AssertEqual(test4.Denominator(), 1, "заданный конструктор с 0 числителем (знаменатель)");

	Rational test5(5, 7);
	AssertEqual(test5.Numerator(), 5, "заданный конструктор (числитель)");
	AssertEqual(test5.Denominator(), 7, "заданный конструктор (знаменатель)");


}

void TestNegative() {
	Rational test1(-1, -2);
	AssertEqual(test1.Numerator(), 1, "отрицательные числ. и зн. (числитель)");
	AssertEqual(test1.Denominator(), 2, "отрицательные числ. и зн. (знаменатель)");

	Rational test2(1, -2);
	AssertEqual(test2.Numerator(), -1, "пол. числ. и отр.  зн. (числитель)");
	AssertEqual(test2.Denominator(), 2, "пол. числ. и отр.  зн. (знаменатель)");

	Rational test3(-5, -10);
	AssertEqual(test3.Numerator(), 1, "отрицательные числ. и зн. (числитель)");
	AssertEqual(test3.Denominator(), 2, "отрицательные числ. и зн. (знаменатель)");

	Rational test4(-10, -5);
	AssertEqual(test4.Numerator(), 2, "отрицательные числ. и зн. (числитель)");
	AssertEqual(test4.Denominator(), 1, "отрицательные числ. и зн. (знаменатель)");

	Rational test5(3, -6);
	AssertEqual(test5.Numerator(), -1, "пол. числ. и отр.  зн. (числитель)");
	AssertEqual(test5.Denominator(), 2, "пол. числ. и отр.  зн. (знаменатель)");

	Rational test6(6, -2);
	AssertEqual(test6.Numerator(), -3, "пол. числ. и отр.  зн. (числитель)");
	AssertEqual(test6.Denominator(), 1, "пол. числ. и отр.  зн. (знаменатель)");
}

int main() {
  TestRunner runner;

  runner.RunTest(TestConstructor, "TestConstructor");
  runner.RunTest(TestNegative, "TestNegative");

  return 0;
}

/* авторское решение
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

void TestPredefined() {
  AssertEqual(Rational(1, 1).Numerator(), 1, "Canonical form of 1/1 is 1/1");
  AssertEqual(Rational(1, 1).Denominator(), 1, "Canonical form of 1/1 is 1/1");
  AssertEqual(Rational(3, 5).Numerator(), 3, "Canonical form of 3/5 is 3/5");
  AssertEqual(Rational(3, 5).Denominator(), 5, "Canonical form of 3/5 is 3/5");
  AssertEqual(Rational(2147483647, 2147483647).Numerator(), 1, "Canonical form of 2147483647/2147483647 is 1/1");
  AssertEqual(Rational(2147483647, 2147483647).Denominator(), 1, "Canonical form of 2147483647/2147483647 is 1/1");
  AssertEqual(Rational(-5, 4).Numerator(), -5, "Canonical form of -5/4 is -5/4");
  AssertEqual(Rational(-5, 4).Denominator(), 4, "Canonical form of -5/4 is -5/4");
  AssertEqual(Rational(5, -4).Numerator(), -5, "Canonical form of 5/-4 is -5/4");
  AssertEqual(Rational(5, -4).Denominator(), 4, "Canonical form of 5/-4 is -5/4");
  AssertEqual(Rational(-6, -2).Numerator(), 3, "Canonical form of -6/-2 is 3/1");
  AssertEqual(Rational(-6, -2).Denominator(), 1, "Canonical form of -6/-2 is 3/1");
  AssertEqual(Rational(21, 56).Numerator(), 3, "Canonical form of 21/56 is 3/8");
  AssertEqual(Rational(21, 56).Denominator(), 8, "Canonical form of 21/56 is 3/8");
  AssertEqual(Rational(0, 100).Numerator(), 0, "Canonical form of 0/100 is 0/1");
  AssertEqual(Rational(0, 100).Denominator(), 1, "Canonical form of 0/100 is 0/1");
  AssertEqual(Rational().Numerator(), 0, "Canonical form of default constructed is 0/1");
  AssertEqual(Rational().Denominator(), 1, "Canonical form of default constructed is 0/1");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestPredefined, "TestPredefined");
  return 0;
}
 */
