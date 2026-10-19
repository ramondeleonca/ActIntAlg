#pragma once

template <typename T>
struct NodeD {
    T data;
    NodeD<T>* next;
    NodeD<T>* prev;

    NodeD(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    NodeD(const T& value, NodeD<T>* nextNode, NodeD<T>* prevNode) : data(value), next(nextNode), prev(prevNode) {} 
};