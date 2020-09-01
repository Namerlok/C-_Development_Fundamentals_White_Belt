//============================================================================
// Name        : build_an_arithmetic_exp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Ansi-style
//============================================================================

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <deque>
#include <queue>

using namespace std;

void print_dec(deque<char> str) {
	for(unsigned int i = 0; i < str.size(); ++i){
		cout << str[i];
	}
}

void add_num(deque<char>& str, const string& n) {

	for(const char& i: n) {
		str.push_back(i);
	}
}

int main() {
	int N = 0;
	string a= "";
	cin >> a >> N;

	deque<char> str;
	add_num(str, a);
	for (int i = 0; i < N; ++i) {
		char op = 'a';
		string num = "";
		cin >> op >> num;
		str.push_front('(');
		str.push_back(')');
		str.push_back(' ');
		str.push_back(op);
		str.push_back(' ');
		add_num(str, num);
	}

	print_dec(str);

	return 0;
}

/* авторсоке решение
#include <iostream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

// Определим структуру для удобной организации данных
struct Operation {
  // Параметры по умолчанию нужны для конструирования вектора
  // ненулевого размера (*)
  char type = 0;
  int number = 0;
};

int main() {
  int initial_number;
  cin >> initial_number;

  int number_of_operations;
  cin >> number_of_operations;
  vector<Operation> operations(number_of_operations);  // (*)
  for (int i = 0; i < number_of_operations; ++i) {
    cin >> operations[i].type;
    cin >> operations[i].number;
  }

  deque<string> expression;
  expression.push_back(to_string(initial_number));
  for (const auto& operation : operations) {
    expression.push_front("(");
    expression.push_back(") ");
    expression.push_back(string(1, operation.type));
    expression.push_back(" ");
    expression.push_back(to_string(operation.number));
  }

  for (const string& s : expression) {
    cout << s;
  }

  return 0;
}
 */

