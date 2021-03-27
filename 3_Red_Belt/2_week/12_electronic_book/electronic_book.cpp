#include <iomanip>
#include <map>
#include <iostream>
#include <vector>
#include <utility>
#include "test_runner.h"

class ReadingManager {
public:
    ReadingManager()
    : user_page_counts_(MAX_PAGE_COUNT_ + 1) {}

    void Read(int user_id, int page_count) {
        if (user_page_.find(user_id) == user_page_.end()) {
            User_Count++;
        } else {
            user_page_counts_[user_page_.at(user_id)].erase(user_id);
            user_page_.erase(user_id);
        }
        user_page_counts_[page_count].insert(user_id);
        user_page_[user_id] = page_count;
    }

    double Cheer(int user_id) const {
        if (user_page_.find(user_id) == user_page_.end())
            return 0;

        const int user_count = static_cast<int>(User_Count);
        if (user_count == 1)
            return 1;

        const int page_count = user_page_.at(user_id);
        int quantity_less = 0;

        for (int i = 1; i < page_count; i++)
            quantity_less += static_cast<int>(user_page_counts_[i].size());

        if (quantity_less == 0)
            return 0;

        return quantity_less * 1.0 / (user_count - 1);
    }

private:
    size_t User_Count = 0;
    static const int MAX_PAGE_COUNT_ = 1000;

    std::vector<std::set<int>> user_page_counts_;
    std::map<int, int> user_page_;

    /*
    void AddUser(int user_id) {
        sorted_users_.push_back(user_id);
        user_positions_[user_id] = sorted_users_.size() - 1;
    }
    */

    /*
    void SwapUsers(int lhs_position, int rhs_position) {
        const int lhs_id = sorted_users_[lhs_position];
        const int rhs_id = sorted_users_[rhs_position];
        std::swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
        std::swap(user_positions_[lhs_id], user_positions_[rhs_id]);
    }
    */
};

void Test_Begin();

int main() {
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout

    TestRunner tr;

    tr.RunTest(Test_Begin, "Initial tests ");

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    std::cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        std::string query_type;
        std::cin >> query_type;
        int user_id;
        std::cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            std::cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            std::cout << std::setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}

void Test_Begin() {
    {
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(5), 0.0);
        manager.Read(1, 10);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
        manager.Read(2, 5);
        manager.Read(3, 7);
        ASSERT_EQUAL(manager.Cheer(2), 0.0);
        ASSERT_EQUAL(manager.Cheer(3), 0.5);
        manager.Read(3, 10);
        ASSERT_EQUAL(manager.Cheer(3), 0.5);
        manager.Read(3, 11);
        ASSERT_EQUAL(manager.Cheer(3), 1.0);
        ASSERT_EQUAL(manager.Cheer(1), 0.5);
    }
}

/* author's solution
#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>

using namespace std;

class ReadingManager {
public:
  ReadingManager()
        // -1 значит, что не случилось ни одного READ
      : user_page_counts_(MAX_USER_COUNT_ + 1, -1),
        page_achieved_by_count_(MAX_PAGE_COUNT_ + 1, 0) {}

  void Read(int user_id, int page_count) {
    UpdatePageRange(user_page_counts_[user_id] + 1, page_count + 1);
    user_page_counts_[user_id] = page_count;
  }

  double Cheer(int user_id) const {
    const int pages_count = user_page_counts_[user_id];
    if (pages_count == -1) {
      return 0;
    }
    const int user_count = GetUserCount();
    if (user_count == 1) {
      return 1;
    }
    // По умолчанию деление целочисленное, поэтому
    // нужно привести числитель к типу double.
    // Простой способ сделать это — умножить его на 1.0.
    return (user_count - page_achieved_by_count_[pages_count]) * 1.0
           / (user_count - 1);
  }

private:
  // Статическое поле не принадлежит какому-либо конкретному объекту класса.
  // По сути это глобальная переменная, в данном случае - константная.
  // Будь она публичной, к ней можно было бы обратиться снаружи
  // следующим образом: ReadingManager::MAX_USER_COUNT.
  static const int MAX_USER_COUNT_ = 100'000;
  static const int MAX_PAGE_COUNT_ = 1'000;

  // Номер страницы, до которой дочитал пользователь <ключ>
  vector<int> user_page_counts_;
  // Количество пользователей, дочитавших (как минимум) до страницы <индекс>
  vector<int> page_achieved_by_count_;

  int GetUserCount() const {
    return page_achieved_by_count_[0];
  }

  // lhs включительно, rhs не включительно
  void UpdatePageRange(int lhs, int rhs) {
    for (int i = lhs; i < rhs; ++i) {
      ++page_achieved_by_count_[i];
    }
  }
};


int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}
*/
