#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SortedStrings {
public:
	void AddString(const string& s) {
		strs.push_back(s);
	}
	vector<string> GetSortedStrings() {
		sort (begin(strs), end(strs));
		return strs;
}
private:
	vector<string> strs;
};

void PrintSortedStrings(SortedStrings& strings) {
  for (const string& s : strings.GetSortedStrings()) {
    cout << s << " ";
  }
  cout << endl;
}

int main() {
  SortedStrings strings;

  strings.AddString("first");
  strings.AddString("third");
  strings.AddString("second");
  PrintSortedStrings(strings);

  strings.AddString("second");
  PrintSortedStrings(strings);

  return 0;
}
