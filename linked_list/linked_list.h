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
    Node *next;
    Node(const T &val) : data(val), next(nullptr) {}
  };

  Node *head;
  Node *tail;

  size_t _size;

  void destroy() {
    while (head != nullptr) {
      Node *temp = head;
      head = head->next;
      delete temp;
      temp = nullptr;
    }
  }

public:
  LinkedList() : head(nullptr), tail(nullptr), _size(0) {}
  LinkedList(const LinkedList &other) : head(nullptr), tail(nullptr), _size(0) {
    if (other.head == nullptr) {
      return;
    }

    head = new Node(other.head->data);
    tail = head;
    _size++;

    Node *other_current = other.head->next;

    while (other_current != nullptr) {
      tail->next = new Node(other_current->data);
      tail = tail->next;
      other_current = other_current->next;
      _size++;
    }
  }
  LinkedList &operator=(const LinkedList &other) {
    if (this != &other) {
      destroy();

      if (other.head != nullptr) {
        head = new Node(other.head->data);
        tail = head;
        _size++;

        Node *other_current = other.head->next;

        while (other_current != nullptr) {
          tail->next = new Node(other_current->data);
          tail = tail->next;
          other_current = other_current->next;
          _size++;
        }
      }
    }
    return *this;
  }
  LinkedList(std::initializer_list<T> init)
      : head(nullptr), tail(nullptr), _size(0) {
    for (const T &val : init) {
      Node *new_node = new Node(val);
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
  ~LinkedList() { destroy(); }
  void push_front(const T &value) {
    Node *new_node = new Node(value);
    if (head == nullptr) {
      head = new_node;
      tail = new_node;
    } else {
      new_node->next = head;
      head = new_node;
    }
    _size++;
  }
  void push_back(const T &value) {
    Node *new_node = new Node(value);
    if (head == nullptr) {
      head = new_node;
      tail = new_node;
    } else {
      tail->next = new_node;
      tail = new_node;
    }
  }
  void pop_front() {
    if (head != nullptr) {
      Node *temp = head;
      head = head->next;
      delete temp;
      temp = nullptr;
    }
    _size--;
  }
  T &front() { return head->data; }
  const T &front() const { return head->data; }
  T &back() { return tail->data; }
  const T &back() const { return tail->data; }
  size_t size() { return _size; }
  void print() {
    Node *current = head;
    while (current != nullptr) {
      std::cout << current->data << " ";
      current = current->next;
    }
    std::cout << "\n";
  }
};

#endif
