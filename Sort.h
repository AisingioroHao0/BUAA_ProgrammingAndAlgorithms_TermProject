//
// Created by AisingioroHao on 2022/10/29.
//

#ifndef BUAA_PROGRAMMINGANDALGORITHMS_TERMPROJECT_SORT_H
#define BUAA_PROGRAMMINGANDALGORITHMS_TERMPROJECT_SORT_H
#include <vector>
template<typename T>
class Sort {
public:
    static void SelectionSort(std::vector<T> data);
    static void MergeSort(std::vector<T> data);
    static void QuickSort(std::vector<T> data);
    static void ShellSort(std::vector<T> data);
    static void RadixSort(std::vector<T> data);

};


#endif //BUAA_PROGRAMMINGANDALGORITHMS_TERMPROJECT_SORT_H
