#ifndef SEARCH_ALGORITHM_HPP
#define SEARCH_ALGORITHM_HPP

#include <vector>
#include <stdexcept>

// Búsueda binaria adaptada para buscar límites superior e inferior (La lista ya esta ordenada)
template <typename T, typename K>
int binarySearchLowerBound(const std::vector<T> &list, K key) {
    int left = 0;
    int right = list.size() - 1;
    int result = list.size(); // default if not found (or everything is smaller)

    while (left <= right) {
        int mid = (left + right) / 2;
        if (list[mid].datetimeKey >= key) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return result;
}

template <typename T, typename K>
int binarySearchUpperBound(const std::vector<T> &list, K key) {
    int left = 0;
    int right = list.size() - 1;
    int result = list.size();

    while (left <= right) {
        int mid = (left + right) / 2;
        if (list[mid].datetimeKey > key) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return result;
}

#endif
