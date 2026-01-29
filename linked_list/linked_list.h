#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>

template <typename T> class LinkedList {
private:
  struct Node {
    T data;
    Node* next;
    Node(const T& val) : data(val), next(nullptr) {}
  };

  Node* head;
  Node* tail;
  size_t _size;

public:
  class iterator {
  private:
    Node* current;

  public:
    iterator() : current(nullptr) {}
    iterator(Node* node) : current(node) {}

    T& operator*() const { return current->data; }
    T* operator->() { return &(current->data); }

    iterator& operator++() {
      current = current->next;
      return *this;
    }

    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator==(const iterator& other) const {
      return current == other.current;
    }

    bool operator!=(const iterator& other) const {
      return current != other.current;
    }

    friend class LinkedList;
  };

  iterator begin() { return iterator(head); }
  const iterator cbegin() const { return iterator(head); }

  iterator end() { return iterator(nullptr); }
  const iterator cend() const { return iterator(nullptr); }

  iterator rbegin() { return iterator(tail); }
  const iterator crbegin() const { return iterator(tail); }

  iterator rend() { return iterator(nullptr); }
  const iterator crend() const { return iterator(nullptr); }

  LinkedList() : head(nullptr), tail(nullptr), _size(0) {}
  LinkedList(std::initializer_list<T> init)
      : head(nullptr), tail(nullptr), _size(0) {
    for (const T& val : init) {
      Node* new_node = new Node(val);
      if (head == nullptr) {
        head = new_node;
        tail = new_node;
      } else {
        tail->next = new_node;
        tail = new_node;
      }
      _size++;
    }
  }
  LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), _size(0) {
    if (other.head == nullptr) { return; }
    head = new Node(other.head->data);
    tail = head;
    _size++;
    Node* other_current = other.head->next;
    while (other_current != nullptr) {
      tail->next = new Node(other_current->data);
      tail = tail->next;
      other_current = other_current->next;
      _size++;
    }
  }
  LinkedList(LinkedList&& other)
      : head(other.head), tail(other.tail), _size(other._size) {
    other.head = nullptr;
    other.tail = nullptr;
    other._size = 0;
  }

  ~LinkedList() { clear(); }

  LinkedList& operator=(const LinkedList& other) {
    if (this == &other) { return *this; }
    clear();
    if (other.head != nullptr) {
      head = new Node(other.head->data);
      tail = head;
      _size++;
      Node* other_current = other.head->next;
      while (other_current != nullptr) {
        tail->next = new Node(other_current->data);
        tail = tail->next;
        other_current = other_current->next;
        _size++;
      }
    }
    return *this;
  }
  LinkedList& operator=(LinkedList&& other) {
    if (this != &other) {
      clear();
      head = other.head;
      tail = other.tail;
      _size = other._size;
      other.head = nullptr;
      other.tail = nullptr;
      other._size = 0;
    }
    return *this;
  }

  T& front() { return head->data; }
  const T& front() const { return head->data; }
  T& back() { return tail->data; }
  const T& back() const { return tail->data; }

  size_t size() const { return _size; }
  bool empty() const { return head == nullptr; }

  void push_front(const T& value) {
    Node* new_node = new Node(value);
    if (head == nullptr) {
      head = new_node;
      tail = new_node;
    } else {
      new_node->next = head;
      head = new_node;
    }
    _size++;
  }
  void push_back(const T& value) {
    Node* new_node = new Node(value);
    if (head == nullptr) {
      head = new_node;
      tail = new_node;
    } else {
      tail->next = new_node;
      tail = new_node;
    }
    _size++;
  }
  void pop_front() {
    if (head == nullptr) { return; }

    Node* temp = head;
    head = head->next;
    delete temp;
    if (head == nullptr) { tail = nullptr; }
    _size++;
  }
  void pop_back() {
    if (head == nullptr) { return; }

    if (head == tail) {
      delete head;
      head = nullptr;
      tail = nullptr;
      _size--;
      return;
    }

    Node* current = head;
    while (current->next != tail) {
      current = current->next;
    }
    delete tail;
    current->next = nullptr;
    tail = current;
    _size--;
  }
  iterator insert_after(iterator pos, const T& value) {
    if (head == nullptr || pos.current == nullptr) { return end(); }

    Node* new_node = new Node(value);
    new_node->next = pos.current->next;
    pos.current->next = new_node;
    if (pos.current == tail) { tail = new_node; }

    _size++;
    return iterator(new_node);
  }
  void clear() {
    while (head != nullptr) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
    tail = nullptr;
    _size = 0;
  }

  void print() const {
    Node* current = head;
    while (current != nullptr) {
      std::cout << current->data << " ";
      current = current->next;
    }
    std::cout << "\n";
  }
};

#endif
