#pragma once

#include <cstdint>
#include <iostream>

#include <algorithm>

template <typename T>
class SimpleVector {
public:
    SimpleVector() = default;
    explicit SimpleVector(size_t size);
    SimpleVector(const SimpleVector& vec);
    SimpleVector(SimpleVector&& vec);
    ~SimpleVector();

    void operator=(SimpleVector<T> vec);
    T& operator[](size_t index);
    T at(size_t index) const;


    T* begin();
    T* end();

    size_t Size() const;
    size_t Capacity() const;
    void PushBack(T value);

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
SimpleVector<T>::SimpleVector(SimpleVector&& vec) :
    size(std::move(vec.Size())), capacity(std::move(vec.Capacity())) {
    data = new T[size];
    for (size_t i = 0; i < size; ++i)
        data[i] = std::move(vec[i]);
}

template <typename T>
void SimpleVector<T>::operator=(SimpleVector vec) {
    size = std::move(vec.Size());
    capacity = std::move(vec.Capacity());
    if (data != nullptr)
        delete[] data;
    data = new T[size];
    for (size_t i = 0; i < size; ++i)
        data[i] = std::move(vec[i]);
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
void SimpleVector<T>::PushBack(T value) {
    if (size >= capacity) {
        auto new_cap = capacity == 0 ? 1 : 2 * capacity;
        auto new_data = new T[new_cap];
        std::move(begin(), end(), new_data);
        delete[] data;
        data = new_data;
        capacity = new_cap;
    }
    data[size++] = std::move(value);
}

template <typename T>
T* SimpleVector<T>::begin() {
    return data;
}

template <typename T>
T* SimpleVector<T>::end() {
    return data + size;
}
