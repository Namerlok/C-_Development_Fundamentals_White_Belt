//============================================================================
// Name        : main.cpp
// Author      : Arkadiy Zagrebelnyi
// Version     :
// Copyright   : Your copyright notice
// Description : Ansi-style
//============================================================================

#include "test_runner.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;

void TestPartOfSet();

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
	vector<T> result;

	for (auto it = begin(elements); it != end(elements); ++it) {
		if (*it > border)
			result.push_back(*it);
	}

	return result;
}

int main() {
	TestRunner test;
	test.RunTest(TestPartOfSet, "TestPartOfSet");
	return 0;
}

void TestPartOfSet() {
	vector<int> s = {7, 8, 9};
	AssertEqual(FindGreaterElements(set<int>{1, 9, 5, 7, 8}, 5), s,
			"Test {1, 9, 5, 7, 8}, find 5");
	vector<string> str = {};
	set<string> se = {"C", "C++"};
	string stri = "Python";
	AssertEqual(FindGreaterElements(se, stri), str,
			"Test {\"C\", \"C++\"}, find \"Python\"");
	vector<int> vector_int = {};
	AssertEqual(FindGreaterElements(set<int>{1, 5, 7, 8}, 8), vector_int,
			"Test {1, 5, 7, 8}, find 8");
}

/* авторское решение
#include <iostream>
#include <set>
#include <vector>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border) {
  // Начнём итерироваться по множеству
  auto it = begin(elements);
  // Цель — найти первый элемент, больший border
  // Если итератор не достиг конца и указывает не туда, двигаем
  while (it != end(elements) && *it <= border) {
  	++it;
  }
  // Возвращаем вектор, созданный из элементов множества, начиная с it
  return {it, end(elements)};
}

 */

