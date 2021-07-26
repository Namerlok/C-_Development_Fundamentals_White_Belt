#pragma once

#include <algorithm>

template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;
    SimpleVector(const SimpleVector& vec);
    explicit SimpleVector(size_t size);
    ~SimpleVector();

    const SimpleVector<T>& operator=(const SimpleVector<T>& vec);
    T& operator[](size_t index);
    T at(size_t index) const;


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
    , capacity(size) {}

template <typename T>
SimpleVector<T>::SimpleVector(const SimpleVector& vec) :
    size(vec.Size()), capacity(vec.Capacity()) {
    data = new T[size];
    for (size_t i = 0; i < size; ++i)
        data[i] = vec.at(i);
}

template <typename T>
const SimpleVector<T>& SimpleVector<T>::operator=(const SimpleVector& vec) {
    size = vec.Size();
    capacity = vec.Capacity();
    if (data != nullptr)
        delete[] data;
    data = new T[size];
    for (size_t i = 0; i < size; ++i)
        data[i] = vec.at(i);
    return vec;
}

template <typename T>
SimpleVector<T>::~SimpleVector() {
    if (data != nullptr)
        delete[] data;
}

template <typename T>
T SimpleVector<T>::at(size_t index) const {
    return data[index];
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


/* author's solution
template <typename T>
class SimpleVector {
public:
  SimpleVector() = default;
  explicit SimpleVector(size_t size);
  SimpleVector(const SimpleVector& rhs);
  ~SimpleVector();

  void operator=(const SimpleVector& rhs) {
    if (rhs.size <= capacity) {
      // У нас достаточно памяти - просто копируем элементы
      copy(rhs.begin(), rhs.end(), begin());
      size = rhs.size;
    } else {
      // Это так называемая идиома copy-and-swap.
      // Мы создаём временный вектор с помощью
      // конструктора копирования, а затем обмениваем его поля со своими.
      // Так мы достигаем двух целей:
      //  - избегаем дублирования кода в конструкторе копирования
      //    и операторе присваивания
      //  - обеспечиваем согласованное поведение конструктора копирования
      //    и оператора присваивания
      SimpleVector<T> tmp(rhs);
      swap(tmp.data, data);
      swap(tmp.size, size);
      swap(tmp.capacity, capacity);
    }
  }

  T& operator[](size_t index);

  T* begin();
  T* end();

  const T* begin() const;
  const T* end() const;

  size_t Size() const;
  size_t Capacity() const;
  void PushBack(const T& value);

private:
  T* data = nullptr;
  size_t size = 0;
  size_t capacity = 0;
};
 */
