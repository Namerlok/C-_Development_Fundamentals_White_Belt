#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "test_runner.h"
#include "profile.h"

class Learner {
    private:
//    std::vector<std::string> dict;
    std::set<std::string> dict;

    public:
    int Learn(const std::vector<std::string>& words) {
/*
        int newWords = 0;
        for (const auto& word : words) {
            if (find(dict.begin(), dict.end(), word) == dict.end()) {
                ++newWords;
                dict.push_back(word);
            }
        } */

        int old_size = static_cast<int>(dict.size());

        for (const auto& word : words)
            dict.insert(word);

        return static_cast<int>(dict.size()) - old_size;
    }

    std::vector<std::string> KnownWords() {
//        sort(dict.begin(), dict.end());
//        dict.erase(unique(dict.begin(), dict.end()), dict.end());
//        return dict;

        return {dict.begin(), dict.end()};
    }
};


int main() {
    Learner learner;
    std::string line;
    while (getline(std::cin, line)) {
        std::vector<std::string> words;
        std::stringstream ss(line);
        std::string word;
        while (ss >> word) {
            words.push_back(word);
        }
        {
        LOG_DURATION("Test struct");
        std::cout << learner.Learn(words) << "\n";
        }
    }
    std::cout << "=== known words ===\n";
    for (const auto& word : learner.KnownWords()) {
        std::cout << word << "\n";
    }
}

/* author's solution
#include <set>
#include <string>
#include <vector>

using namespace std;

class Learner {
 private:
  set<string> dict;

 public:
  int Learn(const vector<string>& words) {
    int newWords = 0;
    for (const auto& word : words) {
      if (dict.find(word) == dict.end()) {
        ++newWords;
        dict.insert(word);
      }
    }
    return newWords;
  }

  vector<string> KnownWords() const {
    return {dict.begin(), dict.end()};
  }
};
*/
