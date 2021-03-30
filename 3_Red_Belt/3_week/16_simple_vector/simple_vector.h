#pragma once

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <exception>

template <typename T>
class SimpleVector {
public:
    explicit SimpleVector(size_t size): size(size) {
        capacity = size;
        my_vec = new T[capacity];
    }

    SimpleVector() {;}

    ~SimpleVector() {
        if (my_vec != nullptr) {
            delete[] my_vec;
            my_vec = nullptr;
        }
    }

    T& operator[](size_t index) {
        return *(my_vec + index);
    }

    T* begin() {
        return my_vec;
    }
    T* end() {
        return my_vec + size;
    }

    const T* begin() const {
        return my_vec;
    }
    const T* end() const {
        return my_vec + size;
    }

    size_t Size() const {
        return size;
    }
    size_t Capacity() const {
        return capacity;
    }
    void PushBack(const T& value) {
        if (capacity == size)
            Realloc_( (capacity == 0) ? (2) : (2 * capacity) );
        else if (capacity < size)
            throw std::out_of_range("out of bounds of allocated memory");
        my_vec[size] = value;
        ++size;
    }

private:
    size_t capacity = 0;
    size_t size = 0;

    T* my_vec = nullptr;

    void Realloc_(size_t new_capacity) {
        T* new_vec = new T[new_capacity];
        capacity = new_capacity;

        if (my_vec != nullptr) {
            memcpy(new_vec, my_vec, size * sizeof (T));
            delete[] my_vec;
            my_vec = nullptr;
        }
        my_vec = new_vec;
    }
};

/* author's solution
#pragma once

#include <algorithm>
using namespace std;

template <typename T>
class SimpleVector {
public:
  SimpleVector() = default;
  explicit SimpleVector(size_t size);
  ~SimpleVector();

  T& operator[](size_t index);

  T* begin();
  T* end();

  size_t Size() const;
  size_t Capacity() const;
  void PushBack(const T& value);

private:
  T* data = nullptr;
  size_t size = 0;
  size_t capacity = 0;
};

template <typename T>
SimpleVector<T>::SimpleVector(size_t size)
  : data(new T[size])
  , size(size)
  , capacity(size)
{
}

template <typename T>
SimpleVector<T>::~SimpleVector() {
  delete[] data;
}

template <typename T>
T& SimpleVector<T>::operator[](size_t index) {
  return data[index];
}

template <typename T>
size_t SimpleVector<T>::Size() const {
  return size;
}

template <typename T>
size_t SimpleVector<T>::Capacity() const {
  return capacity;
}

template <typename T>
void SimpleVector<T>::PushBack(const T& value) {
  if (size >= capacity) {
    auto new_cap = capacity == 0 ? 1 : 2 * capacity;
    auto new_data = new T[new_cap];
    copy(begin(), end(), new_data);
    delete[] data;
    data = new_data;
    capacity = new_cap;
  }
  data[size++] = value;
}

template <typename T>
T* SimpleVector<T>::begin() {
  return data;
}

template <typename T>
T* SimpleVector<T>::end() {
  return data + size;
}

 */
