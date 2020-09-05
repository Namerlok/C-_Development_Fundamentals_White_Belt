//============================================================================
// Name        : grouping_strings_by_prefix
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Ansi-style
//============================================================================

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

bool comp_1(const string& val, const string& word) {
//	for(unsigned int i = 0; i < val.size(); ++i)
//		if (val.at(i) > word.at(i))
//			return false;
//	return true;
	int min_size = min(end(val) - begin(val), end(word) - begin(word));
	bool b = lexicographical_compare(begin(val), begin(val) + min_size,
			begin(word), begin(word) + min_size);
	bool m = equal(begin(val), end(val), begin(word));
//	cout << "b = " << b << " m = " << m << endl;

	return m || b;
}

bool comp_2(const string& val, const string& word) {

	int min_size = min(end(val) - begin(val), end(word) - begin(word));
	return lexicographical_compare(begin(val), begin(val) + min_size,
			begin(word), begin(word) + min_size);
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    const string& prefix) {

	return make_pair(upper_bound(range_begin, range_end, prefix, &comp_1),
			upper_bound(range_begin, range_end, prefix, &comp_2));
}

int main() {
  const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

  const auto mo_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
  for (auto it = mo_result.first; it != mo_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;

  const auto mt_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
  cout << (mt_result.first - begin(sorted_strings)) << " " <<
      (mt_result.second - begin(sorted_strings)) << endl;

  const auto na_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
  cout << (na_result.first - begin(sorted_strings)) << " " <<
      (na_result.second - begin(sorted_strings)) << endl;

  return 0;
}

/* авторское решение
#include <algorithm>
#include <utility>
#include <string>


template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
	RandomIt range_begin, RandomIt range_end, string prefix) {

  // Все строки, начинающиеся с prefix, больше или равны строке "<prefix>"
  auto left = lower_bound(range_begin, range_end, prefix);

  // Составим строку, которая в рамках буквенных строк является
  // точной верхней гранью множества строк, начинающихся с prefix
  string upper_bound = prefix;
  ++upper_bound[upper_bound.size() - 1];

  // Первое встреченное слово, не меньшее upper_bound,
  // обязательно является концом полуинтервала
  auto right = lower_bound(range_begin, range_end, upper_bound);

  return {left, right};
}
 */

