#include <iostream>
#include <vector>
using namespace std;

void Scanf_Vector (vector<int> &days) {
	for (int i = 0; i < (int)days.size(); i++) {
		cin >> days[i];
	}
}

int Avarage_Temp (const vector<int> &days) {

	int avtemp = 0;
	for (auto i : days)
		avtemp += i;
	avtemp /= days.size();

	return avtemp;
}

void Print_Vector(const vector<int> &answer) {
	for (int i : answer)
		cout << i << " ";
	cout << endl;
}

int main() {

	int N;
	cin >> N;
	vector<int> days(N);
	vector<int> answer;
	Scanf_Vector (days);

	int avtemp = Avarage_Temp (days);

	for (int i = 0; i < N; i++)
		if (days[i] > avtemp)
			answer.push_back(i);
	cout << answer.size() << endl;
	Print_Vector(answer);

	return 0;
}
