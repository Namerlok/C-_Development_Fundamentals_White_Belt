/*
 * sum_reverse_sort.cpp
 *
 *  Created on: 16 июл. 2020 г.
 *      Author: Zarka
 */

#include "sum_reverse_sort.h"
#include <algorithm>
template <class swap_t>
void Swap(swap_t &val1, swap_t &val2) {
	swap_t s;
	s = val1;
	val1 = val2;
	val2 = s;
}
int Sum(int x, int y) {
	return x + y;
}

string Reverse(string s) {
	for(unsigned int i = 0; i < s.size() / 2; ++i)
		Swap(s[i], s[s.size() - i - 1]);
	return s;
}

void Sort(vector<int>& nums) {
	sort(nums.begin(), nums.end());
}



