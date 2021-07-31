#include "profile.h"
#include "test_runner.h"
#include "paginator.h"
#include <vector>
#include <future>
//#include <thread>

const size_t MATRIX_SIZE = 7000;
const size_t MATRIX_PAGE_SIZE = 2000;

template <typename T>
int64_t CalculateSinglMatrixSum(const T& matrix) {
    int64_t result = 0;
    for (const auto& line: matrix) {
        for (const auto& el: line) {
            result += el;
        }
    }
    return result;
}

int64_t CalculateMatrixSum(const std::vector<std::vector<int>>& matrix) {
    int64_t result = 0;
    std::vector<std::future<int64_t>> futures;
    for (const auto& page: Paginate(matrix, MATRIX_PAGE_SIZE)) {
        futures.push_back(std::async([page] {return CalculateSinglMatrixSum(page);}));
    }

    for (auto& fut: futures) {
        result += fut.get();
    }

    return result;
}


template <typename ContainerOfVectors>
void GenerateSingleThread(ContainerOfVectors & result,
                          size_t first_row, size_t column_size) {
    for (auto& row : result) {
        row.reserve(column_size);
        for (size_t column = 0; column < column_size; ++column) {
            row.push_back(first_row ^ column);
        }
        ++first_row;
    }
}

std::vector<std::vector<int>> GenerateMultiThread(size_t size, size_t page_size) {
    std::vector<std::vector<int>> result(size);
    std::vector<std::future<void>> futures ;
    size_t first_row = 0;
    for (auto page : Paginate(result , page_size )) {
        futures.push_back(std::async(
            [page , first_row , size] {
                GenerateSingleThread(page , first_row , size);
            }
        ));
        first_row += page_size;
    }
    return result ;
}

void TestCalculateMatrixSum() {
    {
//        const std::vector<std::vector<int>> matrix = {
//             1, 2, 3, 4},
//            {5, 6, 7, 8},
//            {9, 10, 11, 12},
//            {13, 14, 15, 16}
//        };
//        ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
    }
    {
        const std::vector<std::vector<int>> matrix = GenerateMultiThread(MATRIX_SIZE, MATRIX_PAGE_SIZE);
        ASSERT_EQUAL(CalculateMatrixSum(matrix), 195928050144);
    }
}

void TestCalculateSingleMatrixSum() {
    {
//        const std::vector<std::vector<int>> matrix = {
//            {1, 2, 3, 4},
//            {5, 6, 7, 8},
//            {9, 10, 11, 12},
//            {13, 14, 15, 16}
//        };
//        ASSERT_EQUAL(CalculateSinglMatrixSum(matrix), 136);
    }
    {
        const std::vector<std::vector<int>> matrix = GenerateMultiThread(MATRIX_SIZE, MATRIX_PAGE_SIZE);
        ASSERT_EQUAL(CalculateSinglMatrixSum(matrix), 195928050144);
    }
}


int main() {
    LOG_DURATION("Total");
    TestRunner tr;
    {
        LOG_DURATION("Single sum");
        RUN_TEST(tr, TestCalculateSingleMatrixSum);
    }
    {
        LOG_DURATION("Multi sum");
        RUN_TEST(tr, TestCalculateMatrixSum);
    }
    return 0;
}

/* author's solution
#include <algorithm>
#include <cstdint>
#include <vector>
#include <future>
using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
    , size_(distance(first, last))
  {
  }

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

  size_t size() const {
    return size_;
  }

private:
  Iterator first, last;
  size_t size_;
};

template <typename Iterator>
class Paginator {
private:
  vector<IteratorRange<Iterator>> pages;

public:
  Paginator(Iterator begin, Iterator end, size_t page_size) {
    for (size_t left = distance(begin, end); left > 0; ) {
      size_t current_page_size = min(page_size, left);
      Iterator current_page_end = next(begin, current_page_size);
      pages.push_back({begin, current_page_end});

      left -= current_page_size;
      begin = current_page_end;
    }
  }

  auto begin() const {
    return pages.begin();
  }

  auto end() const {
    return pages.end();
  }

  size_t size() const {
    return pages.size();
  }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator(begin(c), end(c), page_size);
}

template <typename ContainerOfVectors>
int64_t SumSingleThread(const ContainerOfVectors& matrix) {
  int64_t sum = 0;
  for (const auto& row : matrix) {
    for (auto item : row) {
      sum += item;
    }
  }
  return sum;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
  vector<future<int64_t>> futures;
  for (auto page : Paginate(matrix, 2000)) {
    futures.push_back(async([=] { return SumSingleThread(page); }));
  }
  int64_t result = 0;
  for (auto& f : futures) {
    result += f.get();
  }
  return result;
}
 */
