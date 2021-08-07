#pragma once

#include "iterator_range.h"

#include <string_view>
#include <string>
#include <sstream>
#include <vector>

template <typename Container>
std::string Join(char c, const Container& cont) {
    std::ostringstream os;
    for (const auto& item : Head(cont, cont.size() - 1)) {
        os << item << c;
    }
    os << *rbegin(cont);
    return os.str();
}

std::string_view Strip(std::string_view s);
std::vector<std::string_view> SplitBy(std::string_view s, char sep);
//std::vector<std::string> SplitIntoWords(const std::string& line);
void LeftStrip(std::string_view& sv);
std::string_view ReadToken(std::string_view& sv);
std::vector<std::string_view> SplitIntoWords(std::string_view line);

/* author's solution
#pragma once

#include "iterator_range.h"

#include <string_view>
#include <sstream>
#include <vector>
using namespace std;

template <typename Container>
string Join(char c, const Container& cont) {
  ostringstream os;
  for (const auto& item : Head(cont, cont.size() - 1)) {
    os << item << c;
  }
  os << *rbegin(cont);
  return os.str();
}

string_view Strip(string_view s);
vector<string_view> SplitBy(string_view s, char sep);
void LeftStrip(string_view& sv);
string_view ReadToken(string_view& sv);

vector<string_view> SplitIntoWordsView(string_view str);
 */
