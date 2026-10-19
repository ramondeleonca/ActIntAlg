#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP

#include <vector>
#include "DoublyLinkedList/DoublyLinkedList.h"

template <typename T>
void swapElements(std::vector<T> &list, int i, int j) {
    if (i != j) {
        T aux = list[i];
        list[i] = list[j];
        list[j] = aux;
    }
}

template <typename T>
void bubbleSort(std::vector<T> &list) {
    bool change = true;
    for (int i=list.size()-1; i>0 && change; i--) {
        change = false;
        for (int j=0; j<i; j++) {
            if (list[j] > list[j+1]) {
                change = true;
                swapElements(list, j, j+1);
            }
        }
    }
}

template <typename T>
void insertionSort(std::vector<T> &list) {
    for (int i=1; i<list.size(); i++) {
        bool exit = false;
        for (int j=i; j>0 && !exit; j--) {
            if (list[j] < list[j-1]) {
               swapElements(list, j, j-1); 
            } else {
                exit = true;
            }
        }
    }
}

template <typename T>
void merge(std::vector<T> &list, int left, int mid, int right) {
    std::vector<T> leftList;
    for (int i=left; i<=mid; i++) {
        leftList.push_back(list[i]);
    }
    std::vector<T> rightList;
    for (int j=mid+1; j<=right; j++) {
        rightList.push_back(list[j]);
    }
    int index = left;
    int i=0;
    int j=0;
    while (i<leftList.size() && j<rightList.size()) {
        if (leftList[i] < rightList[j] || leftList[i] == rightList[j]) {
            list[index] = leftList[i];
            i++;
        } else {
            list[index] = rightList[j];
            j++;
        }
        index++;
    }
    while (i<leftList.size()) {
        list[index] = leftList[i];
        i++;
        index++;
    }
    while (j<rightList.size()) {
        list[index] = rightList[j];
        j++;
        index++;
    }
}

template <typename T>
void mergeSort(std::vector<T> &list, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(list, left, mid);
        mergeSort(list, mid+1, right);
        merge(list, left, mid, right);
    }
}

template <typename T>
void mergeSort(std::vector<T> &list) {
    if (!list.empty()) {
        mergeSort(list, 0, list.size() - 1);
    }
}

// ─────────────────────────────────────────────
//  Algoritmos de ordenamiento para DoublyLinkedList
// ─────────────────────────────────────────────

// Divide la lista en dos mitades usando apuntadores slow/fast
template <typename T>
NodeD<T>* splitHalf(NodeD<T>* head) {
    NodeD<T>* slow = head;
    NodeD<T>* fast = head->next;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    NodeD<T>* mid = slow->next;
    slow->next = nullptr;
    if (mid != nullptr) mid->prev = nullptr;
    return mid;
}

// Fusiona dos listas ordenadas; estable (<= conserva orden relativo)
template <typename T>
NodeD<T>* mergeLists(NodeD<T>* left, NodeD<T>* right, long long& comparaciones) {
    NodeD<T> dummy(T{});
    NodeD<T>* cur = &dummy;
    dummy.prev = nullptr;

    while (left != nullptr && right != nullptr) {
        comparaciones++;
        if (left->data <= right->data) {
            cur->next = left;
            left->prev = cur;
            left = left->next;
        } else {
            cur->next = right;
            right->prev = cur;
            right = right->next;
        }
        cur = cur->next;
    }
    if (left != nullptr) {
        cur->next = left;
        left->prev = cur;
    } else {
        cur->next = right;
        if (right != nullptr) right->prev = cur;
    }

    NodeD<T>* result = dummy.next;
    if (result != nullptr) result->prev = nullptr;
    return result;
}

// Merge Sort recursivo para lista doble
template <typename T>
NodeD<T>* mergeSortRec(NodeD<T>* head, long long& comparaciones, int depth, int& maxDepth) {
    if (depth > maxDepth) maxDepth = depth;
    if (head == nullptr || head->next == nullptr) return head;

    NodeD<T>* mid = splitHalf(head);

    head = mergeSortRec(head, comparaciones, depth + 1, maxDepth);
    mid  = mergeSortRec(mid,  comparaciones, depth + 1, maxDepth);

    return mergeLists(head, mid, comparaciones);
}

// Interfaz de Merge Sort para DoublyLinkedList
template <typename T>
void mergeSort(DoublyLinkedList<T>& lista, long long& comparaciones, int& maxDepth) {
    comparaciones = 0;
    maxDepth = 0;

    NodeD<T>* newHead = mergeSortRec(lista.getHead(), comparaciones, 0, maxDepth);
    lista.setHead(newHead);

    NodeD<T>* cur = newHead;
    NodeD<T>* prev = nullptr;
    while (cur != nullptr) {
        cur->prev = prev;
        prev = cur;
        if (cur->next == nullptr) lista.setTail(cur);
        cur = cur->next;
    }
    if (newHead == nullptr) lista.setTail(nullptr);
}

// Quick Sort para DoublyLinkedList
template <typename T>
void swapNodeData(NodeD<T>* a, NodeD<T>* b) {
    T tmp = a->data;
    a->data = b->data;
    b->data = tmp;
}

template <typename T>
NodeD<T>* midNode(NodeD<T>* lo, NodeD<T>* hi) {
    NodeD<T>* slow = lo;
    NodeD<T>* fast = lo;
    while (fast != hi && fast->next != hi) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

template <typename T>
void medianOfThree(NodeD<T>* lo, NodeD<T>* hi, long long& comparaciones) {
    NodeD<T>* mid = midNode(lo, hi);
    comparaciones++;
    if (lo->data > mid->data) swapNodeData(lo, mid);
    comparaciones++;
    if (lo->data > hi->data)  swapNodeData(lo, hi);
    comparaciones++;
    if (mid->data > hi->data) swapNodeData(mid, hi);
}

template <typename T>
NodeD<T>* partition(NodeD<T>* lo, NodeD<T>* hi, long long& comparaciones) {
    T pivot = hi->data;
    NodeD<T>* i = lo->prev;

    for (NodeD<T>* j = lo; j != hi; j = j->next) {
        comparaciones++;
        if (j->data <= pivot) {
            i = (i == nullptr) ? lo : i->next;
            swapNodeData(i, j);
        }
    }
    i = (i == nullptr) ? lo : i->next;
    swapNodeData(i, hi);
    return i;
}

template <typename T>
void quickSortRec(NodeD<T>* lo, NodeD<T>* hi, long long& comparaciones, int depth, int& maxDepth) {
    if (depth > maxDepth) maxDepth = depth;
    if (lo == nullptr || hi == nullptr || lo == hi || hi->next == lo) return;

    medianOfThree(lo, hi, comparaciones);
    NodeD<T>* p = partition(lo, hi, comparaciones);

    quickSortRec(lo, p->prev, comparaciones, depth + 1, maxDepth);
    quickSortRec(p->next, hi, comparaciones, depth + 1, maxDepth);
}

template <typename T>
void quickSort(DoublyLinkedList<T>& lista, long long& comparaciones, int& maxDepth) {
    comparaciones = 0;
    maxDepth = 0;
    if (lista.getHead() == nullptr) return;
    quickSortRec(lista.getHead(), lista.getTail(), comparaciones, 0, maxDepth);
}

#endif
