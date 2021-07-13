#pragma once

#include "http_request.h"

#include <sstream>
#include <iostream>
#include <string>
#include <string_view>
#include <map>

class Stats {
public:
    void AddMethod(std::string_view method) {
        if (method == "GET")
            ++Methods["GET"];
        else if (method == "POST")
            ++Methods["POST"];
        else if (method == "PUT")
            ++Methods["PUT"];
        else if (method == "DELETE")
            ++Methods["DELETE"];
        else
            ++Methods["UNKNOWN"];
    }
    void AddUri(std::string_view uri) {
        if (uri == "/")
            ++Uri["/"];
        else if (uri == "/order")
            ++Uri["/order"];
        else if (uri == "/product")
            ++Uri["/product"];
        else if (uri == "/basket")
            ++Uri["/basket"];
        else if (uri == "/help")
            ++Uri["/help"];
        else
            ++Uri["unknown"];
    }

    const std::map<std::string_view, int>& GetMethodStats() const {
        return Methods;
    };
    const std::map<std::string_view, int>& GetUriStats() const {
        return Uri;
    }

private:
    std::map<std::string_view, int> Methods =
            {{"GET", 0}, {"POST", 0}, {"PUT", 0},
             {"DELETE", 0}, {"UNKNOWN", 0}};
    std::map<std::string_view, int> Uri =
            {{"/", 0}, {"/order", 0}, {"/product", 0},
             {"/basket", 0}, {"/help", 0}, {"unknown", 0}};
};

HttpRequest ParseRequest(std::string_view line);

/* author's solution
#pragma once

#include "http_request.h"

#include <array>
#include <string_view>
#include <map>
using namespace std;

class StatPiece {
public:
  template <typename Container>
  StatPiece(const Container& known_keys, string_view default_key)
    : default_key(default_key)
  {
    counts[default_key] = 0;
    for (string_view key : known_keys) {
      counts[key] = 0;
    }
  }

  void Add(string_view value);

  const map<string_view, int>& GetValues() const {
    return counts;
  }

private:
  const string_view default_key;
  map<string_view, int> counts;
};

class Stats {
public:
  Stats() = default;

  void AddMethod(string_view method);
  void AddUri(string_view uri);
  const map<string_view, int>& GetMethodStats() const;
  const map<string_view, int>& GetUriStats() const;

private:
  // Ключевое слово inline позволяет определить статические члены
  // known_methods, default_method и т.д. здесь, в .h-файле. Без
  // него нам бы пришлось объявить их здесь, а определеление вынести
  // в stats.cpp
  inline static const array<string, 4> known_methods = {"GET", "POST", "DELETE", "PUT"};
  inline static const string default_method= "UNKNOWN";

  inline static const array<string, 5> known_uris = {"/", "/product", "/basket", "/help", "/order"};
  inline static const string default_uri = "unknown";

  StatPiece methods{known_methods, default_method};
  StatPiece uris{known_uris, default_uri};
};

HttpRequest ParseRequest(string_view line);
*/
