//============================================================================
// Name        : 19_main.cpp
// Author      : Arkadiy Zagrebelnyi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "test_runner.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

vector<string> SplitIntoWords(const string& s);
void TestMain();

int main() {
	TestRunner test;
	test.RunTest(TestMain, "TestMain");
	return 0;
}

vector<string> SplitIntoWords(const string& s) {
	vector<string> result;
//	auto begins = begin(s), ends = end(s);
//	while ( (ends = s.find(' ')) != end(s)) {
//		result.push_back(string(begins, ends - 1));
//		begins = ends + 1;
//	}

	auto it = begin(s);
	unsigned int skip = 0;
	while(skip < s.size()){
		auto space = find_if(it + skip, end(s), [](char ch){return ch == ' ';});
		result.push_back(string(it + skip, space));
		skip += space + 1 - (it + skip);
	}


	return result;
}

void TestMain() {
	string s = "C Cpp Java Python";
	vector<string> words = {"C", "Cpp", "Java", "Python"};
	AssertEqual(SplitIntoWords(s), words);
}

/* авторское решение
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

vector<string> SplitIntoWords(const string& str) {
  // Готовим вектор, в который будем сохранять слова
  vector<string> result;

  // Эти два итератора будут ограничивать текущую не разбитую часть строки
  // str_begin будет двигаться вправо
  auto str_begin = begin(str);
  // str_end всегда будет указывать на конец строки (поэтому он константный)
  const auto str_end = end(str);

  // У цикла нет условия завершения, так что единственный способ закончить его —
  // сделать break
  while (true) {

    // Находим первый пробел в текущем «хвосте» строки
    auto it = find(str_begin, str_end, ' ');

    // Полуинтервал [str_begin, it) — очередное слово
    result.push_back(string(str_begin, it));

    if (it == str_end) {
      // Если пробелов больше нет, цикл пора завершить.
      // Последнее слово уже добавлено
      break;
    } else {
      // Иначе первый символ после пробела — начало очередного слова.
      // Туда и подвинем str_begin
      str_begin = it + 1;
    }

  }

  return result;
}
 */

