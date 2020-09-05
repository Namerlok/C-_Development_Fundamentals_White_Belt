//============================================================================
// Name        : 17_Part_of_vector.cpp
// Author      : Arkadiy Zagrebelnyi
// Version     :
// Copyright   : Your copyright notice
// Description : Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include "test_runner.h"

using namespace std;

void PrintVectorPart(const vector<int>& numbers);
//void TestPartOfVector();

int main() {
	PrintVectorPart({6, 1, 8, -5, 4});
	cout << endl;
	PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
	cout << endl;
	PrintVectorPart({6, 1, 8, 5, 4});
	cout << endl;

	return 0;
}

void PrintVectorPart(const vector<int>& numbers) {
	int i = 0;
	for (; i < static_cast<int>(numbers.size()); ++i) {
		if (numbers[i] < 0) {
			--i;
			for (; i >= 0; --i)
				cout << numbers[i] << " ";
			return;
		}
	}
	--i;
	for (;i >= 0; --i)
		cout << numbers[i] << " ";
}

/* авторское решение
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void PrintVectorPart(const vector<int>& numbers) {
  auto negative_it = find_if(
    numbers.begin(), numbers.end(),
    [](int number) {
      return number < 0;
    }
  );

  for (auto it = negative_it; it != numbers.begin(); ) {
    cout << *(--it) << " ";
  }
}
 */

