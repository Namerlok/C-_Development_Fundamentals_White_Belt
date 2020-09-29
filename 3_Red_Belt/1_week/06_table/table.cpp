//============================================================================
// Name        : table.cpp
// Author      : Namerlok
// Version     :
// Copyright   : Your copyright notice
// Description : Ansi-style
//============================================================================

#include "test_runner.h"

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Table{
public:
	Table(const size_t new_height, const size_t new_wigth) :
		height(new_height), width(new_wigth)
	{
		table.resize(height);

		for (size_t i = 0; i < height; ++i)
			table[i].resize(width);
	}

	void Resize (const size_t new_height, const size_t new_wigth) {
		vector<vector<T>> new_table;

		new_table.resize(new_height);

		for (size_t i = 0; i < new_height; ++i)
			new_table[i].resize(new_wigth);

		for (size_t i = 0; i < new_height && i < height; ++i)
			for (size_t h = 0; h < new_wigth && h < width; ++h)
				new_table[i][h] = table[i][h];

		table = new_table;
		height = new_height;
		width = new_wigth;
	}

	pair<size_t, size_t> Size() const {
		if (height == 0 || width == 0)
			return make_pair(0, 0);

		return make_pair(height, width);
	}

	vector<T>& operator[] (size_t it) {
		return table[it];
	}

	const vector<T>& operator[] (size_t it) const {
		return table[it];
	}

private:
	size_t height;
	size_t width;
	vector<vector<T>> table;
};

void TestTable() {
	Table<int> t(1, 1);
	ASSERT_EQUAL(t.Size().first, 1u);
	ASSERT_EQUAL(t.Size().second, 1u);
	t[0][0] = 42;
	ASSERT_EQUAL(t[0][0], 42);
	t.Resize(3, 4);
	ASSERT_EQUAL(t.Size().first, 3u);
	ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestTable);
	return 0;
}

/* авторское решение
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class Table {
 private:
  vector<vector<T>> data;

 public:
  Table(size_t rows, size_t columns) {
    Resize(rows, columns);
  }

  const vector<T>& operator [] (size_t idx) const {
    return data[idx];
  }

  vector<T>& operator [] (size_t idx) {
    return data[idx];
  }

  void Resize(size_t rows, size_t columns) {
    data.resize(rows);
    for (auto& item : data) {
      item.resize(columns);
    }
  }

  pair<size_t, size_t> Size() const {
    if (!data.empty() && !data[0].empty()) {
      return {data.size(), data[0].size()};
    }

    return  {0, 0};
  }

};
 */

