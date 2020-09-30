//============================================================================
// Name        : dec_based_on_two_vectors.cpp
// Author      : Namerlok
// Version     :
// Copyright   : Your copyright notice
// Description : Ansi-style
//============================================================================

#include "test_runner.h"

#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class Deque {
public:
	Deque() = default;

	bool Empty() const {
		return (size_head + size_tail == 0) ? true : false;
	}

	void PushFront(T el) {
		++size_head;
		head.push_back(el);
	}

	void PushBack(T el) {
		++size_tail;
		tail.push_back(el);
	}

	T& Front() {
		if (size_head == 0)
			return tail.front();
		else
			return head.back();
	}

	const T& Front() const {
		if (size_head == 0)
			return tail.front();
		else
			return head.back();
	}

	T& Back() {
		if (size_tail == 0)
			return head.front();
		else
			return tail.back();
	}

	const T& Back() const {
		if (size_tail == 0)
			return head.front();
		else
			return tail.back();
	}

	T& operator[] (size_t index) {
		if (index < size_head) {
			return head[size_head - 1 - index];
		} else {
			index -= size_head;
			return tail[index];
		}
	}

	const T& operator[] (size_t index) const {
		if (index < size_head) {
			return head[size_head - 1 - index];
		} else {
			index -= size_head;
			return tail[index];
		}
	}

	T& At(size_t index) {
		if (index >= Deque::Size()) {
			throw out_of_range{"going beyond the deck"};
		}

		if (index < size_head) {
			return head[size_head - 1 - index];
		} else {
			index -= size_head;
			return tail[index];
		}
	}

	const T& At(size_t index)  const {
		if (index >= Deque::Size()) {
			throw out_of_range{"going beyond the deck"};
		}

		if (index < size_head) {
			return head[size_head - 1 - index];
		} else {
			index -= size_head;
			return tail[index];
		}
	}

	size_t Size() const {
		return size_head + size_tail;
	}

private:
	size_t size_head = 0;
	size_t size_tail = 0;
	vector<T> head;
	vector<T> tail;
};

void TestDeque();


int main() {
	TestRunner tr;
	RUN_TEST(tr, TestDeque);
	return 0;
}

void TestDeque() {
	{
		Deque<int> q;
		ASSERT_EQUAL(q.Size(), 0u);
	}

	{
		Deque<int> q;
		q.PushFront(1);
		ASSERT_EQUAL(q.Size(), 1u);
	}

	{
		Deque<int> q;
		q.PushBack(1);
		ASSERT_EQUAL(q.Size(), 1u);
	}

	{
		Deque<int> q;
		q.PushFront(7);
		ASSERT_EQUAL(q.Front(), 7);
		q.PushFront(123);
		q.PushBack(434);
		ASSERT_EQUAL(q.Front(), 123);
	}

	{
		Deque<int> q;
		q.PushBack(7);
		ASSERT_EQUAL(q.Back(), 7);
		q.PushFront(123);
		q.PushBack(434);
		ASSERT_EQUAL(q.Back(), 434);
	}

	{
		Deque<int> q;
		q.PushBack(123);
		ASSERT_EQUAL(q.Front(), 123);
	}

	{
		Deque<int> q;
		q.PushFront(123);
		ASSERT_EQUAL(q.Back(), 123);
	}

	{
		Deque<int> q;
		q.PushFront(10);
		q.PushFront(21);
		q.PushFront(32);
		ASSERT_EQUAL(q[0], 32);
		ASSERT_EQUAL(q[1], 21);
		ASSERT_EQUAL(q[2], 10);
		q[0] = 131;
		ASSERT_EQUAL(q[0], 131);
	}
	{
		Deque<int> q;
		q.PushBack(10);
		q.PushBack(21);
		q.PushBack(32);
		ASSERT_EQUAL(q[0], 10);
		ASSERT_EQUAL(q[1], 21);
		ASSERT_EQUAL(q[2], 32);
	}
	{
		try {
			Deque<int> q;
			q.PushFront(10);
			ASSERT_EQUAL(q.At(0), 10);
			q.At(2);
		} catch (out_of_range& e) {
//			ASSERT_EQUAL(e.what(), "going beyond the deck");
		}
	}
	{
		Deque<int> q;
		ASSERT(q.Empty());
		q.PushFront(10);
		ASSERT(!q.Empty());
	}
}

/* авторское решение
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class Deque {
 private:
  vector<T> head, tail;

  T& AtImpl(size_t i) {
    return i < head.size() ? head[head.size() - i - 1] : tail[i - head.size()];
  }

  // Вынужденно дублируем код для случая, если у нас на Deque будет константная
  // ссылка
  // В последующих материалах курса мы узнаем, как избавиться от подобного
  // дублирования кода
  const T& AtImpl(size_t i) const {
    return i < head.size() ? head[head.size() - i - 1] : tail[i - head.size()];
  }

  void CheckIndex(size_t i) const {
    if (i >= Size())
      throw out_of_range("Index is out of range");
  }

 public:
  Deque() = default;

  bool Empty() const {
    return head.empty() && tail.empty();
  }

  size_t Size() const {
    return head.size() + tail.size();
  }

  const T& operator [] (size_t i) const {
    return AtImpl(i);
  }

  T& operator [] (size_t i) {
    return AtImpl(i);
  }

  const T& At(size_t i) const {
    CheckIndex(i);
    return AtImpl(i);
  }

  T& At(size_t i) {
    CheckIndex(i);
    return AtImpl(i);
  }

  const T& Front() const {
    return head.empty() ? tail.front() : head.back();
  }

  T& Front() {
    return head.empty() ? tail.front() : head.back();
  }

  const T& Back() const {
    return tail.empty() ? head.front() : tail.back();
  }

  T& Back() {
    return tail.empty() ? head.front() : tail.back();
  }

  void PushFront(const T& elem) {
    head.push_back(elem);
  }

  void PushBack(const T& elem) {
    tail.push_back(elem);
  }
};
 */

