#include "test_runner.h"

#include <iostream>
#include <string>
#include <list>
#include <vector>

class FootballTeem {
public:

    void add_footballer(const int num_pl, const int plase) {
        teem_position[num_pl] = teem.insert(teem_position[plase], num_pl);
    }

    auto begin() const {
        return teem.begin();
    }

    auto end() const {
        return teem.end();
    }


    size_t size() const {
        return teem.size();
    }

private:
    const size_t MAX_SIZE_FOOTBALLER = 100'000;
    using Position = std::list<int>::iterator;

    std::list<int> teem;
    std::vector<Position> teem_position = std::vector<Position>(MAX_SIZE_FOOTBALLER + 1, teem.end());

};

std::ostream& operator<<(std::ostream& out, const FootballTeem& football_teem) {
    for (const auto& footballer: football_teem)
        out << footballer << "\n";
    return out;
}

void TestDefault();

int main() {

    {
        TestRunner tr;
        RUN_TEST(tr, TestDefault);
    }

    int number_iterations = 0;
    std::cin >> number_iterations;

    FootballTeem football_teem;

    for (int i = 0; i < number_iterations; ++i) {
        int num_pl = 0, plase = 0;
        std::cin >> num_pl >> plase;
        football_teem.add_footballer(num_pl, plase);
    }

    std::cout << football_teem;

    return 0;
}

void TestDefault() {
    {
        FootballTeem football_teem;
        football_teem.add_footballer(42, 0);
        football_teem.add_footballer(17, 42);
        football_teem.add_footballer(13, 0);
        football_teem.add_footballer(123, 42);
        football_teem.add_footballer(5, 13);
        std::ostringstream out;
        out << football_teem;
        ASSERT_EQUAL(out.str(), "17\n123\n42\n5\n13\n");
    }
}

/* author's solution
#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main() {
  const int MAX_ATHLETES = 100'000;
  using Position = list<int>::iterator;

  int n_athletes;
  cin >> n_athletes;

  list<int> row;
  vector<Position> athlete_pos(MAX_ATHLETES + 1, row.end());

  for (int i = 0; i < n_athletes; ++i) {
    int athlete, next_athlete;
    cin >> athlete >> next_athlete;
    athlete_pos[athlete] = row.insert(
        athlete_pos[next_athlete],
        athlete
    );
  }

  for (int x : row) {
    cout << x << '\n';
  }
  return 0;
}
 */
