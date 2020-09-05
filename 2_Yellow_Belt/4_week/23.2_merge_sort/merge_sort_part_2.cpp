//============================================================================
// Name        : merge_sort_part_2
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

	MergeSort(begin(elements), begin(elements) + size / 3);
	MergeSort(begin(elements) + size / 3, begin(elements) + 2 * size / 3);
	MergeSort(begin(elements) + 2 * size / 3, end(elements));

	vector<typename RandomIt::value_type> sw;
	merge(begin(elements), begin(elements) + size / 3,
			begin(elements) + size / 3, begin(elements) + 2 * size / 3,
			back_inserter(sw));
	merge(begin(sw), end(sw),
			begin(elements) + 2 * size / 3, end(elements),
			range_begin);
}

int main() {
	vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
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

  // 3. Разбиваем вектор на три равные части
  auto one_third = elements.begin() + range_length / 3;
  auto two_third = elements.begin() + range_length * 2 / 3;

  // 4. Вызываем функцию MergeSort от каждой трети вектора
  MergeSort(elements.begin(), one_third);
  MergeSort(one_third, two_third);
  MergeSort(two_third, elements.end());

  // 5. С помощью алгоритма merge cливаем первые две трети во временный вектор
  // back_inserter -> http://ru.cppreference.com/w/cpp/iterator/back_inserter
  vector<typename RandomIt::value_type> interim_result;
  merge(elements.begin(), one_third, one_third, two_third,
        back_inserter(interim_result));

  // 6. С помощью алгоритма merge сливаем отсортированные части
  // в исходный диапазон
  // merge -> http://ru.cppreference.com/w/cpp/algorithm/merge
  merge(interim_result.begin(), interim_result.end(), two_third, elements.end(),
        range_begin);
}
 */

