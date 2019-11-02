#include <iostream>
#include <vector>
using namespace std;

void Reverse (vector<int>& numbers) {

	int swap = 0;
	for (int i = 0; i < (int)numbers.size() / 2; i++) {
//		cout << "numbers[i] = " << numbers[i] << ", numbers[(int)numbers.size() - 1 - i] = " << numbers[(int)numbers.size() - 1 - i] << endl;
		swap = numbers[i];
		numbers[i] = numbers[(int)numbers.size() - 1 - i];
		numbers[(int)numbers.size() - 1 - i] = swap;
	}
}

int main() {

	vector<int> numbers = {1, 5, 3, 4, 2};
	Reverse (numbers);
	// numbers должен оказаться равен {2, 4, 3, 5, 1}

	for (auto i : numbers) {
		cout << i << " ";
	}
	return 0;
}
