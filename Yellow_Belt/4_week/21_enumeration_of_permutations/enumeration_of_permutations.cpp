//============================================================================
// Name        : 21_enumeration_of_permutations.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <typename el>
ostream& operator<<(ostream& out, const vector<el> vec) {
	for(auto n: vec){
		out << n << " ";
	}
	return out;
}

int main() {

	int n = 0;
	cin >> n;

	vector<int> per(n);
	for(int i = 0; i < n; ++i)
		per[i] = n - i;

	do {
		cout << per << endl;
	} while (prev_permutation(begin(per), end(per)));

	return 0;
}

/* авторское решение
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
  int range_length;
  cin >> range_length;
  vector<int> permutation(range_length);

  // iota             -> http://ru.cppreference.com/w/cpp/algorithm/iota
  // Заполняет диапазон последовательно возрастающими значениями
  // Обратные итераторы позволяют заполнить его, двигаясь от конца к началу
  iota(permutation.rbegin(), permutation.rend(), 1);

  // prev_permutation ->
  //     http://ru.cppreference.com/w/cpp/algorithm/prev_permutation
  // Преобразует диапазон в предыдущую (лексикографически) перестановку,
  // если она существует, и возвращает true,
  // иначе (если не существует) - в последнюю (наибольшую) и возвращает false
  do {
    for (int num : permutation) {
      cout << num << ' ';
    }
    cout << endl;
  } while (prev_permutation(permutation.begin(), permutation.end()));

  return 0;
}
 */

