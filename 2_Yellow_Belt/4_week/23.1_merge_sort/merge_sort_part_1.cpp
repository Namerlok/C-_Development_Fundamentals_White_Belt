//============================================================================
// Name        : merge_sort_part_1
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	int size = 0;
	if ((size = range_end - range_begin) < 2)
		return;
	vector<typename RandomIt::value_type> elements(range_begin, range_end);

	MergeSort(begin(elements), begin(elements) + size / 2);
	MergeSort(begin(elements) + size / 2, end(elements));

	merge(begin(elements), begin(elements) + size / 2,
			begin(elements) + size / 2, end(elements),
			range_begin);
}

int main() {
	vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
	MergeSort(begin(v), end(v));
	for (int x : v) {
		cout << x << " ";
	}
	cout << endl;
	return 0;
}

/* авторское решение
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  // 1. Если диапазон содержит меньше 2 элементов, выходим из функции
  int range_length = range_end - range_begin;
  if (range_length < 2) {
    return;
  }

  // 2. Создаем вектор, содержащий все элементы текущего диапазона
  vector<typename RandomIt::value_type> elements(range_begin, range_end);

  // 3. Разбиваем вектор на две равные части
  auto mid = elements.begin() + range_length / 2;

  // 4. Вызываем функцию MergeSort от каждой половины вектора
  MergeSort(elements.begin(), mid);
  MergeSort(mid, elements.end());

  // 5. С помощью алгоритма merge сливаем отсортированные половины
  // в исходный диапазон
  // merge -> http://ru.cppreference.com/w/cpp/algorithm/merge
  merge(elements.begin(), mid, mid, elements.end(), range_begin);
}
 */

