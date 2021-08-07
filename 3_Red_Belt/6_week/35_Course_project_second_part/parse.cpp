#include "parse.h"

#include <string_view>
#include <iostream>
#include <iterator>
#include <vector>
#include <future>

std::string_view Strip(std::string_view s) {
    while (!s.empty() && isspace(s.front())) {
        s.remove_prefix(1);
    }
    while (!s.empty() && isspace(s.back())) {
        s.remove_suffix(1);
    }
    return s;
}

std::vector<std::string_view> SplitBy(std::string_view s, char sep) {
    std::vector<std::string_view> result;
    while (!s.empty()) {
        size_t pos = s.find(sep);
        result.push_back(s.substr(0, pos));
        s.remove_prefix(pos != s.npos ? pos + 1 : s.size());
    }
    return result;
}

void LeftStrip(std::string_view& sv) {
  while (!sv.empty() && isspace(sv[0])) {
    sv.remove_prefix(1);
  }
}

std::string_view ReadToken(std::string_view& sv) {
  LeftStrip(sv);

  auto pos = sv.find(' ');
  auto result = sv.substr(0, pos);
  sv.remove_prefix(pos != sv.npos ? pos : sv.size());
  return result;
}

std::vector<std::string_view> SplitIntoWords(std::string_view str) {
  std::vector<std::string_view> result;

  for (std::string_view word = ReadToken(str); !word.empty(); word = ReadToken(str)) {
    result.push_back(word);
  }

  return result;
}

// wrong solution
//std::vector<std::string_view> SplitIntoWords(std::string_view line) {
//    std::vector<std::string_view> result;
//    while (!line.empty()) {
//        while (!line.empty() && isspace(line.front()))
//            line.remove_prefix(1);
//        size_t pos = line.find(' ');
//        result.push_back(line.substr(0, pos));
//        line.remove_prefix(pos != line.npos ? pos + 1 : line.size());
//    }
//    return result;
//}

/* author's solution
#include "parse.h"

string_view Strip(string_view s) {
  while (!s.empty() && isspace(s.front())) {
    s.remove_prefix(1);
  }
  while (!s.empty() && isspace(s.back())) {
    s.remove_suffix(1);
  }
  return s;
}

vector<string_view> SplitBy(string_view s, char sep) {
  vector<string_view> result;
  while (!s.empty()) {
    size_t pos = s.find(sep);
    result.push_back(s.substr(0, pos));
    s.remove_prefix(pos != s.npos ? pos + 1 : s.size());
  }
  return result;
}

void LeftStrip(string_view& sv) {
  while (!sv.empty() && isspace(sv[0])) {
    sv.remove_prefix(1);
  }
}

string_view ReadToken(string_view& sv) {
  LeftStrip(sv);

  auto pos = sv.find(' ');
  auto result = sv.substr(0, pos);
  sv.remove_prefix(pos != sv.npos ? pos : sv.size());
  return result;
}

vector<string_view> SplitIntoWordsView(string_view str) {
  vector<string_view> result;

  for (string_view word = ReadToken(str); !word.empty(); word = ReadToken(str)) {
    result.push_back(word);
  }

  return result;
}
 */
