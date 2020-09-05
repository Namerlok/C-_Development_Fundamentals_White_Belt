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

bool IsPalindrom(const string& str) {
	for (unsigned int i = 0; i < str.size() / 2; ++i) {
		if (str[i] != str[str.size() - i - 1])
			return false;
	}
	return true;
}

void Test() {
	Assert(IsPalindrom(""), "пустая строка");
	Assert(IsPalindrom("madam"), "madam");
	Assert(IsPalindrom("level"), "level");
	Assert(IsPalindrom("wasitacaroracatisaw"), "wasitacaroracatisaw");
	Assert(IsPalindrom(""), "void string");
	Assert(IsPalindrom(" "), "single char");
	Assert(IsPalindrom("&"), "single char");
	Assert(IsPalindrom("   "), "only space in string");
	Assert(IsPalindrom("# ## #"), "non letters string");
	Assert(IsPalindrom("   m   "), "any string");
	Assert(IsPalindrom("abcd !!_ ! _!! dcba"), "stranger palindrom");
	Assert(IsPalindrom("  "), "two spaces");
	Assert(IsPalindrom("a b c d d c b a"), "");
	Assert(IsPalindrom("aa"), "two symbols");
	Assert(IsPalindrom("adcda"), "\"adcda\"");
	Assert(IsPalindrom("a"), "a");
	Assert(IsPalindrom("A"), "A");
	Assert(IsPalindrom(" "), " ");
	Assert(IsPalindrom("&"), "&");
	Assert(IsPalindrom("      "), "only space in string");
	Assert(IsPalindrom("   m   "), "any string");
	Assert(IsPalindrom("# ## #"), "non letters string");
	Assert(IsPalindrom("  "), "two spaces");
	Assert(IsPalindrom("a c a"), "\"a c a\"");
	Assert(IsPalindrom("123321"), "\"123321\"");
	Assert(IsPalindrom("12a21"), "\"12a21\"");
	Assert(IsPalindrom("madam"), "\"madam\"");
	Assert(IsPalindrom("level"), "\"level\"");
	Assert(IsPalindrom("aa"), "two symbols");
	Assert(IsPalindrom("a b c d d c b a"), "");
	Assert(IsPalindrom("wasitacaroracatisaw"), "\"wasitacaroracatisaw\"");
	Assert(IsPalindrom("1"), "1");
	Assert(IsPalindrom("!*&()^%$#@{}[]:;\"\'?~~?\'\";:][}{@#$%^)(&*!"), "\"!*&()^%$#@{}[]:;\"\'?~~?\'\";:][}{@#$%^)(&*!\"");
//	Assert(IsPalindrom("/№.,=<>><=,.№/"), "\"/№№/\"");

	Assert(!IsPalindrom("adcda "), "\"adcda \"");
	Assert(!IsPalindrom("a ca"), "\"a ca\"");
	Assert(!IsPalindrom(" m  m  "), "nearly palindrom");
	Assert(!IsPalindrom("1ad1a1"), "\"1ad1a1\"");
	Assert(!IsPalindrom("adcd"), "\"adcd\"");
	Assert(!IsPalindrom("         -          "), "a lot of space");
	Assert(!IsPalindrom("qwertyuiop][poiuytrewq"), "\"qwertyuiop[][poiuytrewq\"");
	Assert(!IsPalindrom("skvdlvldiewv"), "random string");
	Assert(!IsPalindrom("ab"), "two symbols");
	Assert(!IsPalindrom("a b c d d c b  a"), "");
	Assert(!IsPalindrom("skvdlvldiewv"), "random string");
	Assert(!IsPalindrom(" m  m  "), "nearly palindrom");
	Assert(!IsPalindrom("abcd !_!! dcba"), "nearly palindrom-2");
	Assert(!IsPalindrom("abcddcba "), "ignore space");
	Assert(!IsPalindrom(" abcddcba"), "ignore space-2");
	Assert(!IsPalindrom("         -          "), "a lot of space");
	Assert(!IsPalindrom("a b c d d c b  a"), "");
	Assert(!IsPalindrom("ab"), "two symbols");
}

int main() {
	TestRunner runner;

	runner.RunTest(Test, "Test");

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

void TestIsPalindrom() {
  Assert(IsPalindrom(""), "empty string is a palindrome");
  Assert(IsPalindrom("a"), "one letter string is a palindrome");
  Assert(IsPalindrom("abba"), "abba is a palindrome");
  Assert(IsPalindrom("abXba"), "abXba is a palindrome");
  Assert(IsPalindrom("a b X b a"), "`a b X b a` is a palindrome");
  Assert(IsPalindrom("  ABBA  "), "`  ABBA  ` is a palindrome");

  Assert(!IsPalindrom("XabbaY"), "XabbaY is not a palindrome");
  Assert(!IsPalindrom("abXYba"), "abXYba is not a palindrome");
  Assert(!IsPalindrom("Xabba"), "Xabba is not a palindrome");
  Assert(!IsPalindrom("abbaX"), "abbaX is not a palindrome");
  Assert(
    !IsPalindrom("was it a car or a cat i saw"),
    "`was it a car or a cat i saw` is not a palindrome because spaces do not match"
  );
  Assert(!IsPalindrom("ABBA   "), "`ABBA   ` is not a palindrome");
  Assert(!IsPalindrom("  ABBA"), "`  ABBA` is not a palindrome");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestIsPalindrom, "TestIsPalindrom");
  return 0;
}

 */

