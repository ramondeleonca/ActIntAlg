#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP

#include <vector>

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

#endif
