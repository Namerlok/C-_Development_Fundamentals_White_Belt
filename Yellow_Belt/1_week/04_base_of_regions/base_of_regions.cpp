#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <map>

using namespace std;

enum class Lang {
  DE, FR, IT
};

struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};

int FindMaxRepetitionCount(const vector<Region>& regions) {
	if (regions.empty())
		return 0;

	int max_repetitions = 0;
	vector<pair<Region, int>> count_of_regions;

	for (int i = 0; i < (int)regions.size(); ++i) {
		int j = 0;
		for (j = 0; j < (int)count_of_regions.size(); ++j) {
			if (tie(regions[i].std_name, regions[i].parent_std_name, regions[i].names, regions[i].population) ==
					tie (count_of_regions[j].first.std_name, count_of_regions[j].first.parent_std_name, count_of_regions[j].first.names, count_of_regions[j].first.population)) {
				++count_of_regions[j].second;
				break;
			}
/*			if (regions[i].std_name == count_of_regions[j].first.std_name &&
				regions[i].parent_std_name == count_of_regions[j].first.parent_std_name &&
				regions[i].names == count_of_regions[j].first.names &&
				regions[i].population == count_of_regions[j].first.population) {
				++count_of_regions[j].second;
				break;
			}
*/
		}
		if (j == (int)count_of_regions.size())
			count_of_regions.push_back({regions[i], 1});
	}

	for(auto iter: count_of_regions) {
		if (max_repetitions < iter.second)
			max_repetitions = iter.second;
	}

	return max_repetitions;
}

int main() {
  cout << FindMaxRepetitionCount({
      {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      },
  }) << endl;

  cout << FindMaxRepetitionCount({
      {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Russia",
          "Eurasia",
          {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Toulouse",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          89
      }, {
          "Moscow",
          "Russia",
          {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
          31
      },
  }) << endl;

  return 0;
}


