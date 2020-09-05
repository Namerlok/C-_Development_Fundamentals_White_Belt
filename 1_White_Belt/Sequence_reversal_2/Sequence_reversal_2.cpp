#include <iostream>
#include <vector>
using namespace std;


vector<int> Reversed (const vector<int>& numbers) {

	int n = (int)numbers.size();
	vector<int> answer;

	for (int i = 0; i < n; i++) {
		answer.push_back(numbers[n - 1 - i]);
	}

	return answer;
}

int main() {

	vector<int> numbers = {1, 5, 3, 4, 2};
	vector<int> answer;
	answer = Reversed (numbers);

	for (auto i : answer) {
		cout << i << " ";
	}
	return 0;
}
