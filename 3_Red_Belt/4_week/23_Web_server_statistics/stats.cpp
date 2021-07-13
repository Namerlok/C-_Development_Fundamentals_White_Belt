#include "test_runner.h"
#include "http_request.h"
#include "stats.h"

#include <map>
#include <string_view>

HttpRequest ParseRequest(std::string_view line) {
    HttpRequest result;

//    std::cerr << "line = \""<< line << "\"\n";

    while (isspace(line.front()))
        line.remove_prefix(1);

    size_t pos = line.find(" ");
    result.method = line.substr(0, pos);
    line.remove_prefix(pos + 1);

    pos = line.find(" ");
    result.uri = line.substr(0, pos);
    line.remove_prefix(pos + 1);

    pos = line.find(" ");
    result.protocol = line.substr(0, pos);

//    std::cerr << "method = \"" << result.method << "\" "
//              << "uri = \"" << result.uri << "\" "
//              << "protocol = \"" << result.protocol << "\"\n";

    return result;
}

Stats ServeRequests(std::istream& input) {
    Stats result;
    for (std::string line; getline(input, line); ) {
        const HttpRequest req = ParseRequest(line);
        result.AddUri(req.uri);
        result.AddMethod(req.method);
    }
    return result;
    }

void TestBasic() {
    const std::string input =
    R"(GET / HTTP/1.1
    POST /order HTTP/1.1
    POST /product HTTP/1.1
    POST /product HTTP/1.1
    POST /product HTTP/1.1
    GET /order HTTP/1.1
    PUT /product HTTP/1.1
    GET /basket HTTP/1.1
    DELETE /product HTTP/1.1
    GET / HTTP/1.1
    GET / HTTP/1.1
    GET /help HTTP/1.1
    GET /upyachka HTTP/1.1
    GET /unexpected HTTP/1.1
    HEAD / HTTP/1.1)";

    const std::map<std::string_view, int> expected_method_count = {
        {"GET", 8},
        {"PUT", 1},
        {"POST", 4},
        {"DELETE", 1},
        {"UNKNOWN", 1},
    };
    const std::map<std::string_view, int> expected_url_count = {
        {"/", 4},
        {"/order", 2},
        {"/product", 5},
        {"/basket", 1},
        {"/help", 1},
        {"unknown", 2},
    };

    std::istringstream is(input);
    const Stats stats = ServeRequests(is);

    ASSERT_EQUAL(stats.GetMethodStats(), expected_method_count);
    ASSERT_EQUAL(stats.GetUriStats(), expected_url_count);
}

void TestAbsentParts() {
    // Методы GetMethodStats и GetUriStats должны возвращать словари
    // с полным набором ключей, даже если какой-то из них не встречался

    const std::map<std::string_view, int> expected_method_count = {
        {"GET", 0},
        {"PUT", 0},
        {"POST", 0},
        {"DELETE", 0},
        {"UNKNOWN", 0},
    };
    const std::map<std::string_view, int> expected_url_count = {
        {"/", 0},
        {"/order", 0},
        {"/product", 0},
        {"/basket", 0},
        {"/help", 0},
        {"unknown", 0},
    };
    const Stats default_constructed;

    ASSERT_EQUAL(default_constructed.GetMethodStats(), expected_method_count);
    ASSERT_EQUAL(default_constructed.GetUriStats(), expected_url_count);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
    RUN_TEST(tr, TestAbsentParts);
}

/* author's solution
#include "stats.h"

void Stats::AddMethod(string_view method) {
  methods.Add(method);
}

void Stats::AddUri(string_view uri) {
  uris.Add(uri);
}

const map<string_view, int>& Stats::GetMethodStats() const {
  return methods.GetValues();
}

const map<string_view, int>& Stats::GetUriStats() const {
  return uris.GetValues();
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

HttpRequest ParseRequest(string_view line) {
  auto method = ReadToken(line);
  auto uri = ReadToken(line);
  return {method, uri, ReadToken(line)};
}

void StatPiece::Add(string_view value) {
  if (auto it = counts.find(value); it != counts.end()) {
    ++it->second;
  } else {
    ++counts[default_key];
  }
}
*/
