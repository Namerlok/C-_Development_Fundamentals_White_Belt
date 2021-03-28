#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

template <typename T>
class ObjectPool {
public:
    T* Allocate() {
        if (liberated.size() != 0) {
            T* ptr = liberated.front();
            liberated.pop();
            not_liberated.insert(ptr);
            return ptr;

        } else {
            T* ptr = static_cast<T*>(new  (T));
            allocated.insert(ptr);
            not_liberated.insert(ptr);

            return ptr;
        }

    }

    T* TryAllocate() {
        if (liberated.size() != 0) {
            T* ptr = liberated.front();
            liberated.pop();
            not_liberated.insert(ptr);
            return ptr;
        } else {
            return nullptr;
        }

    }

    void Deallocate(T* object) {
        if (not_liberated.find(object) != not_liberated.end()) {
            liberated.push(object);
            not_liberated.erase(object);
        } else {
            throw std::invalid_argument("Invalid argument of ObjectPool::Deallocate");
        }
    }

    ~ObjectPool() {
        for (auto ptr: allocated)
            delete ptr;
    }

private:
    std::set<T*> allocated;
    std::set<T*> not_liberated;
    std::queue<T*> liberated;
};

void TestObjectPool() {
    ObjectPool<std::string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
    }

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}

/* author's solution
#include "test_runner.h"

#include <algorithm>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate();
  T* TryAllocate();

  void Deallocate(T* object);

  ~ObjectPool();

private:
  queue<T*> free;
  set<T*> allocated;
};

template <typename T>
T* ObjectPool<T>::Allocate() {
  if (free.empty()) {
    free.push(new T);
  }
  auto ret = free.front();
  free.pop();
  allocated.insert(ret);
  return ret;
}

template <typename T>
T* ObjectPool<T>::TryAllocate() {
  if (free.empty()) {
    return nullptr;
  }
  return Allocate();
}

template <typename T>
void ObjectPool<T>::Deallocate(T* object) {
  if (allocated.find(object) == allocated.end()) {
    throw invalid_argument("");
  }
  allocated.erase(object);
  free.push(object);
}

template <typename T>
ObjectPool<T>::~ObjectPool() {
  for (auto x : allocated) {
    delete x;
  }
  while (!free.empty()) {
    auto x = free.front();
    free.pop();
    delete x;
  }
}
 */
