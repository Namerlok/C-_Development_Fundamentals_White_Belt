#include "test_runner.h"

#include <vector>
#include <string>

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = std::vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template <typename Token>
std::vector<Sentence<Token>> SplitIntoSentences(std::vector<Token> tokens) {
    std::vector<Sentence<Token>> result(1);
    size_t pos = 0;
    bool flag = false;
    for (auto& token: tokens) {
        if (!token.IsEndSentencePunctuation() && flag) {
            result.push_back({});
            ++pos;
            flag = false;
        }
        result[pos].push_back(std::move(token));
        if (token.IsEndSentencePunctuation()) {
            flag = true;
        }
    }
    if (result.back().empty())
        result.erase(result.end() - 1);
    return result;
}


struct TestToken {
    std::string data;
    bool is_end_sentence_punctuation = false;

    bool IsEndSentencePunctuation() const {
        return is_end_sentence_punctuation;
    }
    bool operator==(const TestToken& other) const {
        return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }
};

std::ostream& operator<<(std::ostream& stream, const TestToken& token) {
    return stream << token.data;
}


// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() {
    ASSERT_EQUAL(SplitIntoSentences(std::vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
                 std::vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!"}}}));

    ASSERT_EQUAL(SplitIntoSentences(std::vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
                 std::vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!", true}}}));

    ASSERT_EQUAL(SplitIntoSentences(std::vector<TestToken>({{"Split"}, {"into"}, {"sentences"},
                                                            {"!", true}, {"!", true}, {"Without"},
                                                            {"copies"}, {".", true}})),
                 std::vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
                                                   {{"Without"}, {"copies"}, {".", true}},}));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSplitting);
    return 0;
}

/* author's solution
#include "test_runner.h"

#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;


template <typename TokenForwardIt>
TokenForwardIt FindSentenceEnd(TokenForwardIt tokens_begin, TokenForwardIt tokens_end) {
  const TokenForwardIt before_sentence_end =
      adjacent_find(tokens_begin, tokens_end,
                    [](const auto& left_token, const auto& right_token) {
                      return left_token.IsEndSentencePunctuation()
                          && !right_token.IsEndSentencePunctuation();
                    });
  return before_sentence_end == tokens_end
      ? tokens_end
      : next(before_sentence_end);
}

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
  vector<Sentence<Token>> sentences;
  auto tokens_begin = begin(tokens);
  const auto tokens_end = end(tokens);
  while (tokens_begin != tokens_end) {
    const auto sentence_end = FindSentenceEnd(tokens_begin, tokens_end);
    Sentence<Token> sentence;
    for (; tokens_begin != sentence_end; ++tokens_begin) {
      sentence.push_back(move(*tokens_begin));
    }
    sentences.push_back(move(sentence));
  }
  return sentences;
}


struct TestToken {
  string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken& other) const {
    return data == other.data
        && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
  return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() {
  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({
        {"Split"}, {"into"}, {"sentences"}, {"!"}
    })),
    vector<Sentence<TestToken>>({{
        {"Split"}, {"into"}, {"sentences"}, {"!"}
    }})
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({
        {"Split"}, {"into"}, {"sentences"}, {"!", true}
    })),
    vector<Sentence<TestToken>>({{
        {"Split"}, {"into"}, {"sentences"}, {"!", true}
    }})
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({
      {"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true},
      {"Without"}, {"copies"}, {".", true}
    })),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {".", true}},
    })
  );
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSplitting);
  return 0;
}
 */
