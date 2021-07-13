#include "test_runner.h"

#include <cstdio>
#include <array>
#include <iostream>
#include <string>
#include <string_view>
#include <list>

/*
class Editor {
public:
    Editor() = default;

    void Left() {
        if (pos <= 0)
            return;
        --pos;
    }

    void Right() {
        if (pos >= data.size())
            return;
        ++pos;
    }

    void Insert(char token) {
        data.insert(pos, 1, token);
        ++pos;
    }

    void Cut(size_t tokens = 1) {
        buf_cut.clear();
        buf = {""};
        if (tokens == 0)
            return;
        size_t pos_end = (tokens + pos < data.size()) ? (tokens + pos) : (data.size());
        buf_cut = {data.begin() + pos, data.begin() + pos_end};
        data.erase(data.begin() + pos, data.begin() + pos_end);
        buf = std::string_view(buf_cut);
    }

    void Copy(size_t tokens = 1) {
        buf_cut.clear();
        buf = {""};
        if (tokens == 0)
            return;


//        size_t pos_end = (tokens + pos < data.size()) ? (tokens + pos) : (data.size());
//        buf_cut = {data.begin() + pos, data.begin() + pos_end};
//        buf = std::string_view(buf_cut);

        buf = std::string_view(data);
        buf.remove_prefix(pos);
        buf.remove_suffix((tokens + pos < data.size()) ? (data.size() - tokens - pos) : (0));
    }

    void Paste() {
        if (buf.empty())
            return;
        size_t size_str = buf.size();
        data.insert(pos, buf.data(), size_str);
        if (buf_cut.empty() && buf.data() >= &data[pos]) {
            buf = std::string_view(buf.data() + size_str);
//            buf.remove_suffix(data.size() - size_str - pos);
        }
        pos += size_str;
    }

    std::string GetText() const {
        return data;
    }
private:
    size_t pos = 0;
    std::string data = {""};
    std::string_view buf = {""};
    std::string buf_cut = {""};
};
*/

class Editor {
public:
    Editor() = default;

    void Left() {
        if (data.begin() == pos)
            return;
        pos = prev(pos);
        --pos_size;
    }

    void Right() {
//        PrintLog();
        if (data.end() == pos)
            return;
        pos = next(pos);
        ++pos_size;
    }

    void Insert(char token) {
        data.insert(pos, token);
//        pos = next(pos);
        ++pos_size;
    }

    void Cut(size_t tokens = 1) {
        buf.clear();
        if (tokens == 0)
            return;
        std::_List_iterator<char> pos_end =
                (tokens + pos_size < data.size()) ? (next(pos, tokens)) :
                                                    (next(pos, data.size() - pos_size));
        buf = std::list<char>(pos, pos_end);
//        pos_size -= (tokens + pos_size < data.size()) ? (tokens) : (data.size() - pos_size);
        std::_List_iterator<char> pos_ = prev(pos);
        data.erase(pos, pos_end);
        pos = next(pos_);
    }

    void Copy(size_t tokens = 1) {
        buf.clear();
        if (tokens == 0)
            return;
        std::_List_iterator<char> pos_end =
                (tokens + pos_size < data.size()) ? (next(pos, tokens)) :
                                                    (next(pos, data.size() - pos_size));
        buf = std::list<char>(pos, pos_end);
    }

    void Paste() {
        data.insert(pos, buf.begin(), buf.end());
//        pos = next(pos, buf.size());
        pos_size += buf.size();
    }

    std::string GetText() const {
//        PrintLog();
        std::string result;
        for (const auto& it: data)
            result.push_back(it);
        return result;
    }
private:
    std::list<char> data = {};
    std::_List_iterator<char> pos = data.begin();
    size_t pos_size = 0;
    std::list<char> buf = {};

    /*
    void PrintLog() const {
        fprintf(stderr, "\n-------------------------------------------------------\n");
        for (size_t i = 0; i < data.size(); ++i) {
            fprintf(stderr, "data[%i] = \'%c\' (%p)\n", i, *next(data.begin(), i), next(data.begin(), i));
        }
        fprintf(stderr, "pos = (%p) \'%c\'\n", pos, *pos);
        fprintf(stderr, "\n-------------------------------------------------------\n");
    }
    */
};


void TypeText(Editor& editor, const std::string& text) {
    for(char c : text) {
        editor.Insert(c);
    }
}

void TestEditing() {
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");
//        std::cerr << editor.GetText() << "\n";
        for(size_t i = 0; i < text_len; ++i) {
            editor.Left();
        }
        editor.Cut(first_part_len);
        for(size_t i = 0; i < text_len - first_part_len; ++i) {
            editor.Right();
        }

        TypeText(editor, ", ");
        editor.Paste();
        editor.Left();
        editor.Left();
        editor.Cut(3);

        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
    }
    {
    Editor editor;

    TypeText(editor, "Hello, world!");
    editor.Left();
    editor.Cut(5);
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Cut(1);

    ASSERT_EQUAL(editor.GetText(), "Hello! world");
    }
    {
    Editor editor;

    TypeText(editor, "Hello, world!");
    editor.Left();
    editor.Copy(5);
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Cut(1);

    ASSERT_EQUAL(editor.GetText(), "Hello! world!");
    }
    {
    Editor editor;

    TypeText(editor, "Hello, world!");
    editor.Left();
    editor.Copy(5);
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Paste();
    editor.Paste();
    editor.Paste();
    editor.Cut(1);

    ASSERT_EQUAL(editor.GetText(), "Hello!!!! world!");
    }
}

void TestReverse() {
    Editor editor;

    const std::string text = "esreveR";
    for(char c : text) {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    return 0;
}

/* author's solution
#include <list>
#include <string>

using namespace std;

class Editor {
public:
  Editor()
    : pos(text.end()) {
  }

  void Left() {
    pos = Advance(pos, -1);
  }

  void Right() {
    pos = Advance(pos, 1);
  }

  void Insert(char token) {
    text.insert(pos, token);
  }

  void Cut(size_t tokens = 1) {
    auto pos2 = Advance(pos, tokens);
    buffer.assign(pos, pos2);
    pos = text.erase(pos, pos2);
  }

  void Copy(size_t tokens = 1) {
    auto pos2 = Advance(pos, tokens);
    buffer.assign(pos, pos2);
  }

  void Paste() {
    text.insert(pos, buffer.begin(), buffer.end());
  }

  string GetText() const {
    return {text.begin(), text.end()};
  }

private:
  using Iterator = list<char>::iterator;
  list<char> text;
  list<char> buffer;
  Iterator pos;

  Iterator Advance(Iterator it, int steps) const {
    while (steps > 0 && it != text.end()) {
      ++it;
      --steps;
    }
    while (steps < 0 && it != text.begin()) {
      --it;
      ++steps;
    }
    return it;
  }
};
*/
