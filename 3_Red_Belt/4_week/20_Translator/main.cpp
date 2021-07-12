#include "test_runner.h"

#include <string>
#include <iostream>
#include <string_view>
#include <vector>
#include <utility>
#include <algorithm>
#include <deque>
#include <set>
#include <iterator>

/* time limit
typedef std::pair<std::string_view, std::string_view> Translator_T;

class Translator {
public:
    void Add(std::string_view source, std::string_view target) {
        bool check_source_bool = check_source.find(source) == check_source.end();
        bool check_target_bool = check_target.find(target) == check_target.end();

        if (check_source_bool == true && check_target_bool == true) {

            data.push_back(std::string(source));
            std::string_view source_(data.back());
            check_source.insert(source_);

            data.push_back(std::string(target));
            std::string_view target_(data.back());
            check_target.insert(target_);

            data_translator.push_back(make_pair(source_,target_));
        } else if (check_source_bool == false && check_target_bool == true) {
            auto it_view = find_if(data_translator.begin(), data_translator.end(),
                                   [source] (auto& p) {return source == p.first;});
            check_target.erase(it_view->second);
            auto it = find(data.begin(), data.end(), std::string(it_view->second));
            *it = std::string(target);
            check_target.insert(std::string_view(*it));
            it_view->second = std::string_view(*it);
        } else if (check_source_bool == true && check_target_bool == false) {
            auto it_view = find_if(data_translator.begin(), data_translator.end(),
                                   [target] (auto& p) {return target == p.second;});
            check_source.erase(it_view->first);
            auto it = find(data.begin(), data.end(), std::string(it_view->first));
            *it = std::string(source);
            check_source.insert(std::string_view(*it));
            it_view->first = std::string_view(*it);
        } else if (check_source_bool == false && check_target_bool == false) {
            auto it_view_source = find_if(data_translator.begin(), data_translator.end(),
                                          [source] (auto& p) {return source == p.first;});
            if (it_view_source->second == target)
                return;

            check_target.erase(it_view_source->second);
            auto it_source = find(data.begin(), data.end(), std::string(it_view_source->second));
            *it_source = std::string(target);
            check_target.insert(std::string_view(*it_source));
            it_view_source->second = std::string_view(*it_source);

            auto it_view_target = find_if(data_translator.begin(), data_translator.end(),
                                   [target] (auto& p) {return target == p.second;});
            check_source.erase(it_view_target->first);
            auto it_target = find(data.begin(), data.end(), std::string(it_view_target->first));
            *it_target = std::string(source);
            check_source.insert(std::string_view(*it_target));
            it_view_target->first = std::string_view(*it_target);
        }
//        std::cerr << data << "\t";
//        std::cerr << data_translator << "\n";
    }

    std::string_view TranslateForward(std::string_view source) const {
        auto it = find_if(data_translator.begin(), data_translator.end(),
                          [source] (auto& p) {return source == p.first;});
//        std::cerr << "source = " << source << ", it = "<< *it << "\n";
        if (it == data_translator.end())
            return "";
        else
            return it->second;
    }
    std::string_view TranslateBackward(std::string_view target) const {
        auto it = find_if(data_translator.begin(), data_translator.end(),
                          [target] (auto& p) {return target == p.second;});
//        std::cerr << "source = " << target << ", it = "<< *it << "\n";
        if (it == data_translator.end())
            return "";
        else
            return it->first;
    }

private:
    std::deque<Translator_T> data_translator;
    std::deque<std::string> data;
    std::set<std::string_view> check_source;
    std::set<std::string_view> check_target;
};

*/

class Translator {
public:
    void Add(std::string_view source, std::string_view target) {
/*
        auto it = translator_forward.find(source);
        if (it != translator_forward.end())
            translator_target.erase(it->second);

        it = translator_target.find(source);;
        if (it != translator_target.end())
            translator_forward.erase(it->second);
*/
        const std::string_view source_view = GetClonedView(source);
        const std::string_view targer_view = GetClonedView(target);

        translator_forward[source_view] = targer_view;
        translator_target[targer_view] = source_view;
//        std::cerr << data << "\t" << translator_forward << " " << translator_target << "\n";
    }
    std::string_view TranslateForward(std::string_view source) const {
        if (translator_forward.count(source))
            return translator_forward.at(source);
        else
            return {};
    }

    std::string_view TranslateBackward(std::string_view target) const {
        if (translator_target.count(target))
            return translator_target.at(target);
        else
            return {};
    }
private:
    std::deque<std::string> data;
    std::map<std::string_view, std::string_view> translator_forward;
    std::map<std::string_view, std::string_view> translator_target;

    std::string_view GetClonedView(std::string_view str) {
        for (const auto* map_ptr : {&translator_forward, &translator_target}) {
            const auto it = map_ptr->find(str);
                if (it != map_ptr->end()) {
                return it->first;
            }
        }
        return data.emplace_back(str);
    }
};

void TestSimple() {
    Translator translator;
    translator.Add(std::string("okno"), std::string("window"));
    translator.Add(std::string("stol"), std::string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");

    translator.Add(std::string("okno"), std::string("WINDOW"));
    ASSERT_EQUAL(translator.TranslateForward("okno"), "WINDOW");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}

/* author's solution
#include "profile.h"
#include "test_runner.h"
#include <deque>
#include <iostream>
#include <map>
#include <string_view>
#include <vector>

using namespace std;

class Translator {
public:
  void Add(string_view source, string_view target) {
    const string_view source_view = GetClonedView(source);
    const string_view target_view = GetClonedView(target);
    forward_dict[source_view] = target_view;
    backward_dict[target_view] = source_view;
  }
  string_view TranslateForward(string_view source) const {
    return Translate(forward_dict, source);
  }
  string_view TranslateBackward(string_view target) const {
    return Translate(backward_dict, target);
  }

private:
  string_view GetClonedView(string_view s) {
    for (const auto* map_ptr : {&forward_dict, &backward_dict}) {
      const auto it = map_ptr->find(s);
      if (it != map_ptr->end()) {
        return it->first;
      }
    }
    return data.emplace_back(s);
  }

  static string_view Translate(const map<string_view, string_view>& dict, string_view s) {
    if (const auto it = dict.find(s); it != dict.end()) {
      return it->second;
    } else {
      return {};
    }
  }


  map<string_view, string_view> forward_dict;
  map<string_view, string_view> backward_dict;
  deque<string> data;
};
*/
