//============================================================================
// Name        : demographic_indicators.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

enum class Gender {
	FEMALE,
	MALE
};

struct Person {
	int age;			// возраст
	Gender gender;		// пол
	bool is_employed;	// имеет ли работу
};

// Это пример функции, его не нужно отправлять вместе с функцией PrintStats
template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
	if (range_begin == range_end) {
		return 0;
	}
	vector<typename InputIt::value_type> range_copy(range_begin, range_end);
	auto middle = begin(range_copy) + range_copy.size() / 2;
	nth_element(
		begin(range_copy), middle, end(range_copy),
		[](const Person& lhs, const Person& rhs) {
		return lhs.age < rhs.age;
		}
	);
	return middle->age;
}

void PrintStats(vector<Person> persons) {
	cout << "Median age = " << ComputeMedianAge(begin(persons), end(persons)) << endl;
	cout << "Median age for females = " <<
			ComputeMedianAge(begin(persons), partition(begin(persons), end(persons),
			[](const Person& em){return em.gender == Gender::FEMALE;})) << endl;
	cout << "Median age for males = " <<
			ComputeMedianAge(begin(persons), partition(begin(persons), end(persons),
			[](const Person& em){return em.gender == Gender::MALE;})) << endl;
	cout << "Median age for employed females = " <<
			ComputeMedianAge(begin(persons), partition(begin(persons), end(persons),
			[](const Person& em){return em.is_employed && em.gender == Gender::FEMALE;})) << endl;
	cout << "Median age for unemployed females = " <<
			ComputeMedianAge(begin(persons), partition(begin(persons), end(persons),
			[](const Person& em){return !em.is_employed && em.gender == Gender::FEMALE;})) << endl;
	cout << "Median age for employed males = " <<
			ComputeMedianAge(begin(persons), partition(begin(persons), end(persons),
			[](const Person& em){return em.is_employed && em.gender == Gender::MALE;})) << endl;
	cout << "Median age for unemployed males = " <<
			ComputeMedianAge(begin(persons), partition(begin(persons), end(persons),
			[](const Person& em){return !em.is_employed && em.gender == Gender::MALE;})) << endl;
}

int main() {
	vector<Person> persons = {
		{31, Gender::MALE, false},
		{40, Gender::FEMALE, true},
		{24, Gender::MALE, true},
		{20, Gender::FEMALE, true},
		{80, Gender::FEMALE, false},
		{78, Gender::MALE, false},
		{10, Gender::FEMALE, false},
		{55, Gender::MALE, true},
	};
	PrintStats(persons);
	return 0;
}


/* авторское решение
void PrintStats(vector<Person> persons) {
    // Преобразуем порядок людей к следующему:
    //                  persons
    //                 /      \
    //          females        males
    //         /       \     /      \
    //      empl.  unempl. empl.   unempl.
    auto females_end = partition(
        begin(persons), end(persons), [](const Person& p) {
            return p.gender == Gender::FEMALE;
        }
    );
    auto employed_females_end = partition(
        begin(persons), females_end, [](const Person& p) {
            return p.is_employed;
        }
    );
    auto employed_males_end = partition(
        females_end, end(persons), [](const Person& p) {
            return p.is_employed;
        }
    );

    // Теперь интересующие нас группы находятся в векторе непрерывно
    cout << "Median age = "
         << ComputeMedianAge(begin(persons), end(persons))          << endl;
    cout << "Median age for females = "
         << ComputeMedianAge(begin(persons), females_end)           << endl;
    cout << "Median age for males = "
         << ComputeMedianAge(females_end, end(persons))             << endl;
    cout << "Median age for employed females = "
         << ComputeMedianAge(begin(persons),  employed_females_end) << endl;
    cout << "Median age for unemployed females = "
         << ComputeMedianAge(employed_females_end, females_end)     << endl;
    cout << "Median age for employed males = "
         << ComputeMedianAge(females_end, employed_males_end)       << endl;
    cout << "Median age for unemployed males = "
         << ComputeMedianAge(employed_males_end, end(persons))      << endl;
}
 */

