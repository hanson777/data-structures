#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>

template <typename T> class Vector {
private:
  T *data;
  size_t _capacity;
  size_t _size;
  void destroy_and_deallocate(T *&data) {
    for (size_t i = 0; i < _size; i++) {
      data[i].~T();
    }
    operator delete(data);
    data = nullptr;
  }

public:
  Vector() : data(nullptr), _capacity(0), _size(0) {}
  Vector(size_t size)
      : data(static_cast<T *>(operator new(sizeof(T) * size))), _capacity(size),
        _size(size) {
    std::uninitialized_default_construct(data, data + _size);
  }
  Vector(std::initializer_list<T> init)
      : data(static_cast<T *>(operator new(sizeof(T) * init.size()))),
        _capacity(init.size()), _size(init.size()) {
    std::uninitialized_copy(init.begin(), init.end(), data);
  }
  Vector(size_t size, const T &value)
      : data(static_cast<T *>(operator new(sizeof(T) * size))), _size(size),
        _capacity(size) {
    std::uninitialized_fill(data, data + _size, value);
  }
  Vector(const Vector &other)
      : data(static_cast<T *>(operator new(sizeof(T) * other._capacity))),
        _capacity(other._capacity), _size(other._size) {
    std::uninitialized_copy(other.data, other.data + other._size, data);
  }
  Vector &operator=(const Vector &other) {
    if (this != &other) {
      destroy_and_deallocate(data);
      _size = other._size;
      _capacity = other._capacity;
      data = static_cast<T *>(operator new(sizeof(T) * other._capacity));
      std::uninitialized_copy(other.data, other.data + other._size, data);
    }
    return *this;
  }
  Vector(Vector &&other)
      : data(other.data), _capacity(other._capacity), _size(other._size) {
    std::uninitialized_move(other.data, other.data + other._size, data);
    other.data = nullptr;
    other._size = 0;
    other._capacity = 0;
  }
  Vector &operator=(Vector &&other) {
    if (this != &other) {
      destroy_and_deallocate(data);
      data = other.data;
      _size = other._size;
      _capacity = other._capacity;
      other.data = nullptr;
      other._size = 0;
      other._capacity = 0;
    }
    return *this;
  }
  ~Vector() { destroy_and_deallocate(data); }
  void push_back(const T &value) {
    if (_size == _capacity) {
      if (_capacity == 0) {
        _capacity = 1;
      }
      _capacity *= 2;
      T *new_data = static_cast<T *>(operator new(sizeof(T) * _capacity));
      std::uninitialized_move(data, data + _size, new_data);
      destroy_and_deallocate(data);
      data = new_data;
    }
    new (&data[_size]) T(value);
    _size++;
  }
  void pop_back() { data[--_size].~T(); }
  void reserve(const size_t &new_cap) {
    if (new_cap > _capacity) {
      T *new_data = static_cast<T *>(operator new(sizeof(T) * new_cap));
      std::uninitialized_move(data, data + _size, new_data);
      destroy_and_deallocate(data);
      data = new_data;
      _capacity = new_cap;
    }
  }
  T &operator[](size_t index) { return data[index]; }
  const T &operator[](size_t index) const { return data[index]; }
  size_t size() { return _size; }
  size_t capacity() { return _capacity; }
  void print() {
    for (size_t i = 0; i < _size; i++) {
      std::cout << data[i] << ' ';
    }
    std::cout << '\n';
  }
};

#endif
