#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = std::vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;

// Hеализация функции,
// использующая не более 1 копирования каждого символа
/* slow solution
template <typename String>
std::vector<Group<String>> GroupHeavyStrings(std::vector<String> strings) {
    std::vector<Group<String>> result;
    std::vector<std::set<Char<String>>> check_result;
    for (size_t i = 0; i < strings.size(); ++i) {
        std::set<Char<String>> check;
        for (size_t j = 0; j < strings[i].size(); ++j) {
            check.insert(strings[i][j]);
        }
        size_t j = 0;
        for (j = 0; j < check_result.size(); ++j) {
            if (check_result[j] == check) {
                result[j].push_back(std::move(strings[i]));
                break;
            }
        }
        if (j == check_result.size()) {
            check_result.push_back(std::move(check));
            Group<String> item;
            item.push_back(std::move(strings[i]));
            result.push_back(std::move(item));
        }

        if (result.size() != check_result.size())
            throw "Counting error!";
    }
    return result;
}
*/

template <typename String>
String GiveStringOfChars(String result) {
    sort(result.begin(), result.end());
    result.erase(unique(result.begin(), result.end()), result.end());
    return result;
}

template <typename String>
std::vector<Group<String>> GroupHeavyStrings(std::vector<String> strings) {
    std::map<String, Group<String>> data;

    for (auto& string: strings)
        data[GiveStringOfChars(string)].push_back(std::move(string));

    std::vector<Group<String>> result;
    for (auto& [first, second]: data)
        result.push_back(std::move(second));

    return result;
}

void TestGroupingABC() {
    std::vector<std::string> strings = {"caab", "abc", "cccc", "bacc", "c"};
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 2);
    sort(begin(groups), end(groups));  // Порядок групп не имеет значения
    ASSERT_EQUAL(groups[0], std::vector<std::string>({"caab", "abc", "bacc"}));
    ASSERT_EQUAL(groups[1], std::vector<std::string>({"cccc", "c"}));
}

void TestGroupingReal() {
    std::vector<std::string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 4);
    sort(begin(groups), end(groups));  // Порядок групп не имеет значения
    ASSERT_EQUAL(groups[0], std::vector<std::string>({"laptop", "paloalto"}));
    ASSERT_EQUAL(groups[1], std::vector<std::string>({"law", "wall", "awl"}));
    ASSERT_EQUAL(groups[2], std::vector<std::string>({"port"}));
    ASSERT_EQUAL(groups[3], std::vector<std::string>({"top", "pot"}));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestGroupingABC);
    RUN_TEST(tr, TestGroupingReal);
    return 0;
}

/* author's solution
#include <algorithm>
#include <deque>
#include <map>
#include <string>
#include <vector>

using namespace std;

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;

template <typename String>
using Key = String;


template <typename String>
Key<String> ComputeStringKey(const String& string) {
  String chars = string;
  sort(begin(chars), end(chars));
  chars.erase(unique(begin(chars), end(chars)), end(chars));
  return chars;
}


template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
  map<Key<String>, Group<String>> groups_map;
  for (String& string : strings) {
    groups_map[ComputeStringKey(string)].push_back(move(string));
  }
  vector<Group<String>> groups;
  for (auto& [key, group] : groups_map) {
    groups.push_back(move(group));
  }
  return groups;
}
 */
