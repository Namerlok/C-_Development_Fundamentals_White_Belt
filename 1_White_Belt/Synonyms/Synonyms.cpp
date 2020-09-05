/*
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;
*/
/*
void print_vec_set_srt (const vector<set<string>>& v) {
	cout << "start_print#############" << endl;
	for (const auto& i : v) {
		for (const auto& t : i) {
			cout << t << " ";
		}
		cout << endl;
	}
	cout << "end_print###############" << endl;
}

void print_vec_int (const vector<int>& v) {
	cout << "start_print#############" << endl;
	for (const auto& i : v) {
		cout << i << " ";
	}
	cout << endl << "end_print###############" << endl;
}
*/
/*
int main() {

	vector<set<string>> synonyms;
	string word1, word2;
	string command;
	string word;
	int n;
	cin >> n;


	for (int i = 0; i < n; i++) {

		cin >> command;
		if (command == "ADD") {
			set<string> words;
			cin >> word1 >> word2;
			words.insert(word1);
			words.insert(word2);
			bool ch = false;
			for (const auto& sets : synonyms)
				if (sets == words) {
					ch = true;
					break;
				}
			if (!ch)
				synonyms.push_back(words);
//			print_vec_set_srt(synonyms);
		} else if (command == "COUNT") {
			cin >> word;
			int summ = 0;
			for (const auto& sets : synonyms)
				for(const auto& str : sets)
					if (str == word){
						summ++;
						break;
					}
			cout << summ << endl;
		} else if (command == "CHECK") {
			set<string> words;
			cin >> word1 >> word2;
			words.insert(word1);
			words.insert(word2);

			bool ch = false;
			for (const auto& sets : synonyms)
				if (sets == words) {
					ch = true;
					break;
				}
			cout << ((ch) ? "YES" : "NO") << endl;
		}
	}

	return 0;
}
*/

/*
int main() {

	set<set<string>> synonyms;
	string word1, word2;
	string command;
	string word;
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> command;
		if (command == "ADD") {
			set<string> words;
			cin >> word1 >> word2;
			words.insert(word1);
			words.insert(word2);
			synonyms.insert(words);
		} else if (command == "COUNT") {
			cin >> word;
			int summ = 0;
			for (const auto& sets : synonyms)
						summ += sets.count(word);
			cout << summ << endl;
		} else if (command == "CHECK") {
			set<string> words;
			cin >> word1 >> word2;
			words.insert(word1);
			words.insert(word2);
			cout << ((synonyms.count(words)) ? "YES" : "NO") << endl;
		}
	}

	return 0;
}
*/

/*
8
ADD program code
COUNT cipher
ADD code cipher
COUNT code
COUNT program
CHECK code program
CHECK program cipher
CHECK cpp java

 */

