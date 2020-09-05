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

void add_op(deque<char>& str, const char& op_new, const char& op_old) {

	if ((op_new == '*' || op_new == '/') && (op_old == '+' || op_old == '-')) {
		str.push_front('(');
		str.push_back(')');
	}

	str.push_back(' ');
	str.push_back(op_new);
	str.push_back(' ');

//	str.push_front('(');
//	str.push_back(')');
//	str.push_back(' ');
//	str.push_back(op);
//	str.push_back(' ');
}

int main() {
	int N = 0;
	string a= "";
	cin >> a >> N;

	deque<char> str;
	add_num(str, a);
	char op_new = '*', op_old = '*';
	for (int i = 0; i < N; ++i) {
		string num = "";
		op_old = op_new;
		cin >> op_new >> num;
		add_op(str, op_new, op_old);
		add_num(str, num);
	}

	print_dec(str);

	return 0;
}

/* авторсоке решение
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <numeric>
#include <deque>

using namespace std;


// Определим структуру для удобной организации данных
struct Operation {
  // Параметры по умолчанию нужны для конструирования вектора
  // ненулевого размера, см. (*)
  char type = 0;
  int number = 0;
};


// Функция для проверки выполнения требований постановки скобок
bool NeedBrackets(char last, char current) {
  return (last == '+' || last == '-') && (current == '*' || current == '/');
}


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
  // первое число никогда не обрамляется скобками
  char last_type = '*';
  for (const auto& operation : operations) {
    // Если условия удовлетворены, обрамляем последовательность скобками
    if (NeedBrackets(last_type, operation.type)) {
      expression.push_front("(");
      expression.push_back(")");
    }
    expression.push_back(" ");
    expression.push_back(string(1, operation.type));
    expression.push_back(" ");
    expression.push_back(to_string(operation.number));

    last_type = operation.type;
  }

  for (const string& s : expression) {
    cout << s;
  }

  return 0;
}
 */

