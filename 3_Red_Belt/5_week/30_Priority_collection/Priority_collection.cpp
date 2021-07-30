#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <unordered_set>
#include <list>
#include <utility>
#include <vector>
#include <queue>
#include <cstdio>

// Неудачная реализация
// -4 часа жизни (((
// сложно и больно быть идиотом
/*
template <typename T>
class PriorityCollection {
public:
//    using Id = std::_List_iterator<std::pair<T, size_t>>// тип, используемый для идентификаторов ;
    using Id = typename std::list<std::pair<T, int>>::iterator;

    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object) {
        data.push_back(std::make_pair(std::move(object), 0));
//        fprintf(stderr, "%p \n", id);
        return std::prev(data.end());
    }

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
             IdOutputIt ids_begin) {
        while (range_begin != range_end)
            *ids_begin++ = Add(std::move(*range_begin++));
    }

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const {
        if (std::find(data.begin(), data.end(), *id) != data.end())
            return true;
        else
            return false;
    }

    // Получить объект по идентификатору
    const T& Get(Id id) const {
        return id->first;
    }

    // Увеличить приоритет объекта на 1
    void Promote(Id id) {
        for (Id pos = std::prev(id); pos != data.end();) {
//            std::cerr << "(id->second, pos->second) = " << '(' << id->second << ", " << pos->second << ')' << std::endl;
            if (id->second == pos->second) {
//                std::cerr << "{*id, *pos} = " << '{' << *id << ", " << *pos << '}' << std::endl;
                Id prev_it = std::prev(pos);
                data.splice(pos, data, id);
                pos = prev_it;
            } else {
                break;
            }
            if (pos == data.begin())
                break;
        }

        ++(id->second);
    }

    // Получить объект с максимальным приоритетом и его приоритет
    std::pair<const T&, int> GetMax() const {
        return data.front();
    }

    // Аналогично GetMax, но удаляет элемент из контейнера
    std::pair<T, int> PopMax() {
        std::pair<T, int> result = move(*data.begin());
        data.erase(data.begin());
        return result;
    }

    void PrintfData() const {
        std::cerr << "data = " << data << '\t' << std::endl;;
//        for (const auto& el: check)
//            std::cerr << *el;
//        std::cerr << std::endl;
    }

private:
    std::list<std::pair<T, int>> data;

    typedef struct Object {
        T elem;
        int64_t priority = -1;
    } Object;
};
*/

template <typename T>
class PriorityCollection {
public:
    using Id = int;// тип, используемый для идентификаторов

    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object) {
        ++max_id;
        database.push_back(Object(std::move(object)));
        sort_id.insert(std::make_pair(0, max_id));
        return max_id;
    }

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
             IdOutputIt ids_begin) {
        while (range_begin != range_end)
            *ids_begin++ = Add(std::move(*range_begin++));
    }

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const {
        if (id >= 0 && id <= max_id && database[id].priority != no_priority)
            return true;
        else
            return false;
    }

    // Получить объект по идентификатору
    const T& Get(Id id) const {
        return database[id].data;
    }

    // Увеличить приоритет объекта на 1
    void Promote(Id id) {
        auto& item = database[id];
        sort_id.erase(std::make_pair(item.priority, id));
        sort_id.insert(std::make_pair(++item.priority, id));
    }

    // Получить объект с максимальным приоритетом и его приоритет
    std::pair<const T&, int> GetMax() const {
        auto it = std::prev(sort_id.end());
        return {database[it->second].data, it->first};
    }

    // Аналогично GetMax, но удаляет элемент из контейнера
    std::pair<T, int> PopMax() {
        auto it = std::prev(sort_id.end());
        int pr = it->first, id = it->second;
        sort_id.erase(it);
        database[id].priority = no_priority;
        return {std::move(database[id].data), pr};
    }

    void PrintfData() {
        std::cerr << sort_id << std::endl;
        for (const auto& it: sort_id)
            std::cerr << '{' << database[it.second].data << ", "
                      << database[it.second].priority << "} ";
        std::cerr << std::endl;
    }
private:
    struct Object {
        Object(T data): data(std::move(data)) {}
        Object(T data, int priority): data(data), priority(priority) {}

        Object(const Object&) = delete;
        Object(Object&&) = default;
        Object& operator=(const Object&) = delete;
        Object& operator=(Object&&) = default;

        T data;
        int priority = 0;
    };

    std::vector<Object> database;
    int64_t max_id = -1;
    std::set<std::pair<int, Id>> sort_id;

    const int no_priority = -1;
};

class StringNonCopyable : public std::string {
public:
    using std::string::string;  // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
    {
        PriorityCollection<StringNonCopyable> strings;
        //const auto white_id =
                strings.Add("white");
        //strings.PrintfData();
        const auto yellow_id = strings.Add("yellow");
        //strings.PrintfData();
        const auto red_id = strings.Add("red");
        //strings.PrintfData();

        strings.Promote(yellow_id);
        //strings.PrintfData();
        for (int i = 0; i < 2; ++i) {
            strings.Promote(red_id);
            //strings.PrintfData();
        }
        strings.Promote(yellow_id);
        //strings.PrintfData();
        {
            const auto item = strings.PopMax();
            ASSERT_EQUAL(item.first, "red");
            ASSERT_EQUAL(item.second, 2);
        }
        {
            const auto item = strings.PopMax();
            ASSERT_EQUAL(item.first, "yellow");
            ASSERT_EQUAL(item.second, 2);
        }
        {
            const auto item = strings.GetMax();
            ASSERT_EQUAL(item.first, "white");
            ASSERT_EQUAL(item.second, 0);
        }
    }
    {
        PriorityCollection<StringNonCopyable> strings;
        const auto id_Vlad = strings.Add("Vlad");
        const auto id_Ivan = strings.Add("Ivan");
        const auto id_Nadia = strings.Add("Nadia");

        strings.Promote(id_Vlad);
        for (int i = 0; i < 2; ++i)
            strings.Promote(id_Ivan);
        for (int i = 0; i < 3; ++i)
            strings.Promote(id_Nadia);

        ASSERT_EQUAL(strings.Get(id_Vlad), "Vlad");
        ASSERT_EQUAL(strings.Get(id_Ivan), "Ivan");
        ASSERT_EQUAL(strings.Get(id_Nadia), "Nadia");

        {
            const auto item = strings.PopMax();
            ASSERT_EQUAL(item.first, "Nadia");
            ASSERT_EQUAL(item.second, 3);
        }

        ASSERT(strings.IsValid(id_Vlad));
        ASSERT(strings.IsValid(id_Ivan));
        ASSERT(!strings.IsValid(id_Nadia));
    }
    {
        PriorityCollection<StringNonCopyable> strings;
        std::vector<StringNonCopyable> names(3); // = {"Vlad", "Ivan", "Nadia"};
        names[0] = "Vlad";
        names[1] = "Ivan";
        names[2] = "Nadia";
        std::vector<PriorityCollection<StringNonCopyable>::Id> priority(3);
        strings.Add(names.begin(), names.end(), priority.begin());

        ASSERT_EQUAL(strings.Get(priority[0]), "Vlad");
        ASSERT_EQUAL(strings.Get(priority[1]), "Ivan");
        ASSERT_EQUAL(strings.Get(priority[2]), "Nadia");
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}

/* author's solution
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection {
public:
  using Id = int;

  Id Add(T object) {
    const Id new_id = objects.size();
    objects.push_back({move(object)});
    sorted_objects.insert({0, new_id});
    return new_id;
  }

  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin) {
    while (range_begin != range_end) {
      *ids_begin++ = Add(move(*range_begin++));
    }
  }

  bool IsValid(Id id) const {
    return id >= 0 && id < objects.size() &&
        objects[id].priority != NONE_PRIORITY;
  }

  const T& Get(Id id) const {
    return objects[id].data;
  }

  void Promote(Id id) {
    auto& item = objects[id];
    const int old_priority = item.priority;
    const int new_priority = ++item.priority;
    sorted_objects.erase({old_priority, id});
    sorted_objects.insert({new_priority, id});
  }

  pair<const T&, int> GetMax() const {
    const auto& item = objects[prev(sorted_objects.end())->second];
    return {item.data, item.priority};
  }

  pair<T, int> PopMax() {
    const auto sorted_objects_it = prev(sorted_objects.end());
    auto& item = objects[sorted_objects_it->second];
    sorted_objects.erase(sorted_objects_it);
    const int priority = item.priority;
    item.priority = NONE_PRIORITY;
    return {move(item.data), priority};
  }

private:
  struct ObjectItem {
    T data;
    int priority = 0;
  };
  static const int NONE_PRIORITY = -1;

  vector<ObjectItem> objects;
  set<pair<int, Id>> sorted_objects;
};
 */
