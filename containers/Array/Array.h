#ifndef ALIEN_INVASTION_SIMULATOR_ARRAY_H
#define ALIEN_INVASTION_SIMULATOR_ARRAY_H

#include <cstddef>
#include <initializer_list>
#include <algorithm>
#include <iostream>
#include <stdexcept>

template <class T>
class Array {
public:
    Array();
    explicit Array(size_t capacity);
    Array(std::initializer_list<T> list);
    Array(const Array<T> &other);
    Array<T> &operator=(const Array<T> &other);
    Array(Array<T> &&other) noexcept;
    Array<T> &operator=(Array<T> &&other) noexcept;
    ~Array();
    size_t size() const;
    size_t capacity() const;
    bool empty() const;
    T &operator[](size_t index);
    const T &operator[](size_t index) const;
    void clear();
    void push_back(const T &item);
    void push_back(T &&item);
    void print() const;
private:
    T *arr;
    size_t _size;
    size_t _capacity;
    void resize();
};

template<class T>
void Array<T>::print() const {
    std::cout << "Array: content:";
    std::for_each(arr, arr + _size, [](const T &item) {
        std::cout << item << " ";
    });
    std::cout << std::endl;
}

template<class T>
Array<T>::Array() : _size(0), _capacity(1000) {
    arr = new T[_capacity]{};
}

template<class T>
Array<T>::Array(size_t capacity) : _size(0), _capacity(capacity) {
    arr = new T[_capacity]{};
}

template<class T>
Array<T>::Array(std::initializer_list<T> list) : _size(list.size()), _capacity(list.size() * 2) {
    arr = new T[_capacity]{};
    size_t i = 0;
    for (const T &item : list) {
        arr[i++] = item;
    }
}

template<class T>
Array<T>::Array(const Array<T> &other) : _size(other._size), _capacity(other._capacity) {
    arr = new T[_capacity]{};
    std::copy(other.arr, other.arr + _size, arr);
}

template<class T>
Array<T> &Array<T>::operator=(const Array<T> &other) {
    if (this != &other) {
        delete[] arr;
        _size = other._size;
        _capacity = other._capacity;
        arr = new T[_capacity]{};
        std::copy(other.arr, other.arr + _size, arr);
    }
    return *this;
}

template<class T>
Array<T>::Array(Array<T> &&other) noexcept : arr(other.arr), _size(other._size), _capacity(other._capacity) {
    other.arr = nullptr;
    other._size = 0;
    other._capacity = 0;
}

template<class T>
Array<T> &Array<T>::operator=(Array<T> &&other) noexcept {
    if (this != &other) {
        delete[] arr;
        arr = other.arr;
        _size = other._size;
        _capacity = other._capacity;
        other.arr = nullptr;
        other._size = 0;
        other._capacity = 0;
    }
    return *this;
}

template<class T>
Array<T>::~Array() {
    if (arr != nullptr) {
        delete[] arr;
        arr = nullptr;
    }
    _size = 0;
    _capacity = 0;
}

template<class T>
size_t Array<T>::size() const {
    return _size;
}

template<class T>
size_t Array<T>::capacity() const {
    return _capacity;
}

template<class T>
bool Array<T>::empty() const {
    return _size == 0;
}

template<class T>
T &Array<T>::operator[](size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return arr[index];
}

template<class T>
const T &Array<T>::operator[](size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return arr[index];
}

template<class T>
void Array<T>::clear() {
    _size = 0;
}

template<class T>
void Array<T>::push_back(const T &item) {
    if (_size == _capacity) {
        resize();
    }
    arr[_size++] = item;
}

template<class T>
void Array<T>::push_back(T &&item) {
    if (_size == _capacity) {
        resize();
    }
    arr[_size++] = std::move(item);
}

template<class T>
void Array<T>::resize() {
    _capacity <<= 1;
    T *temp = new T[_capacity]{};
    std::copy(arr, arr + _size, temp);
    delete[] arr;
    arr = temp;
}


#endif //ALIEN_INVASTION_SIMULATOR_ARRAY_H
