//
//  MergeSort.cpp
//  distributed_algorithms
//
//  Created by Markiyan Kostiv on 3/8/18.
//  Copyright © 2018 Cardo Systems. All rights reserved.
//

#include "MergeSort.hpp"
#include <vector>
#include <iostream>
#include "tbb.h"
#include "test.h"

using namespace std;

template <class T>
int binarySearch(vector<T>& vector, int first, int last, int value, int position, std::function<bool(int, int)> compare) {
    if (last == first + 1) {
        return compare(value, vector[first]) ? ++position : position;
    }
    
    if (last > first) {
        int middle = first + (last - first) / 2;
        
        if (compare(vector[middle], value)) {
            if (vector[middle] == value) {
                position++;
            }
            return binarySearch(vector, first, middle, value, position, compare);
        }
        return binarySearch(vector, middle, last, value, position + middle - first, compare);
    }
    
    return 0;
}

template <class T>
void parallelMerge(vector<T>& arr, vector<T> firstPart, vector<T> secondPart, int position, std::function<bool(int, int)> compare) {
    tbb::parallel_for(
                      tbb::blocked_range<size_t>(0, firstPart.size()),
                      [&](const tbb::blocked_range<size_t>& r) {
                          for(int i = 0; i < firstPart.size(); i++) {
                              int mergePosition = binarySearch(secondPart,
                                                               0,
                                                               secondPart.size(),
                                                               firstPart[i],
                                                               0,
                                                               compare);
                              arr[position + mergePosition + i] = firstPart[i];
                          }
                      }
                      );
}

template <class T>
void printArr(std::vector<T> arr)
{
    cout << endl;
    for (auto& item: arr)
    {
        cout << item << " ";
    }
    cout << endl;
}

template <class T>
void merge(vector<T>& vector, int first, int middle, int last) {
    std::vector<T> leftPart(vector.begin() + first, vector.begin() + middle);
    std::vector<T> rightPart(vector.begin() + middle, vector.begin() + last);
    
    tbb::parallel_invoke([&] () {
        auto compare = [](int value, int secondValue) -> bool {
            return value > secondValue;
        };

        parallelMerge(vector, leftPart, rightPart, first, compare);
    },
    [&] () {
        auto compare = [](int value, int secondValue) -> bool {
            return value >= secondValue;
        };

        parallelMerge(vector, rightPart, leftPart, first, compare);
    });
}

template <class T>
void mergeSort(vector<T>& vector, int first, int last) {
    if (last > 1 + first) {
        int middle = (last + first) / 2;
        tbb::parallel_invoke([&] () {
            mergeSort(vector, first, middle);
        },
        [&] () {
            mergeSort(vector, middle, last);
        });
        merge(vector, first, middle, last);
    }
    
}

template <class T>
void sort(vector<T>& vector) {
    tbb::task_scheduler_init init(4);
    mergeSort(vector, 0, vector.size());
    printArr(vector);
}
