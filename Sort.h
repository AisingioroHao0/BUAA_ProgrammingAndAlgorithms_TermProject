//
// Created by AisingioroHao on 2022/10/29.
//

#ifndef BUAA_PROGRAMMINGANDALGORITHMS_TERMPROJECT_SORT_H
#define BUAA_PROGRAMMINGANDALGORITHMS_TERMPROJECT_SORT_H

#include <vector>
#include <functional>
#include <thread>
#include <future>
#include "ThreadPool.h"


class Sort {
public:
    template<typename T>
    static void SelectionSort(std::vector<T> &data);

    template<typename T>
    static void MergeSort(std::vector<T> &data);

    template<typename T>
    static void QuickSort(std::vector<T> &data);

    template<typename T>
    static void QuickSortForSimple(std::vector<T> &data);

    template<typename T>
    static void QuickSortSimple(std::vector<T> &data, long long begin, long long end);

    template<typename T>
    static void ShellSort(std::vector<T> &data);

    template<typename T>
    static void RadixSort(std::vector<T> &data);

    template<typename T>
    static void QuickSortMultiThreadByAsync(std::vector<T> &data);

    template<typename T>
    static void MergeSortMultiThreadByAsync(std::vector<T> &data);
};

template<typename T>
/**
 * 选择排序
 * @tparam T 传入数据类型
 * @param data 传入的数据集合
 */
void Sort::SelectionSort(std::vector<T> &data) {
    long long n = data.size();
    for (long long i = 0; i < n; i++) {
        //当前趟最小元素下标
        long long min = i;
        //寻找当前趟的最小元素，并将最小元素的下标赋值给min
        for (long long j = i + 1; j < n; j++) {
            if (data[j] < data[min]) {
                min = j;
            }
        }
        //交换本趟排序的开始元素的下标和当前趟最小元素的下标的值
        std::swap(data[i], data[min]);
    }
}

template<typename T>
void Sort::MergeSort(std::vector<T> &data) {
    std::vector<T> MergeSortBuffer(data.size());
    static std::function<void(int l, int r)> merge_sort = [&data, &MergeSortBuffer](int l, int r) {
        if (l >= r)return;
        int mid = (l + r) / 2;
        merge_sort(l, mid);
        merge_sort(mid + 1, r);
        int i = l, j = mid + 1, p = l;
        while (i <= mid && j <= r) {
            if (data[i] > data[j]) {
                MergeSortBuffer[p++] = data[j++];
            } else {
                MergeSortBuffer[p++] = data[i++];
            }
        }
        while (i <= mid) {
            MergeSortBuffer[p++] = data[i++];
        }
        while (j <= r) {
            MergeSortBuffer[p++] = data[j++];
        }
        for (i = l; i <= r; i++) {
            data[i] = MergeSortBuffer[i];
        }
    };
    if (MergeSortBuffer.size() < data.size()) {
        MergeSortBuffer.resize(data.size());
    }
    merge_sort(0, data.size() - 1);
}

template<typename T>
static void quick_sort(std::vector<T> &data, int l, int r) {
    if (l >= r)return;
    std::swap(data[l], data[l + rand() % (r - l + 1)]);
    int bound1 = l, bound2 = r + 1, i = l + 1;
    while (i < bound2) {
        if (data[i] < data[l]) {
            std::swap(data[i], data[++bound1]);
            i++;
        } else if (data[i] > data[l]) {
            std::swap(data[i], data[--bound2]);
        } else {
            i++;
        }
    }
    std::swap(data[l], data[bound1]);
    quick_sort(data, l, bound1 - 1);
    quick_sort(data, bound2, r);
}

template<typename T>
void Sort::QuickSort(std::vector<T> &data) {
    quick_sort(data, 0, data.size() - 1);
}

/**
 * 快速排序经典型
 * @tparam T 泛型
 * @param data 输入数据
 */
template<typename T>
void Sort::QuickSortForSimple(std::vector<T> &data) {
    QuickSortSimple(data, 0, data.size());
}

/**
 * 快速排序
 * @tparam T 泛型
 * @param data 输入数据
 * @param begin 子问题起点下标
 * @param end 子问题终点下标
 */
template<typename T>
void Sort::QuickSortSimple(std::vector<T> &data, long long begin, long long end) {

    //分治中的治：具体的解决最子问题的逻辑  对比和归并排序：归并排序是先分后治。快速排序是先治后分
    //分的结束条件是begin >= end
    // （比如 2 1 3 子问题1 begin = 0 end = 0 则这个子问题等于已经解出）
    // (比如 2 1 子问题1 begin = 0 end = 0 子问题2 begin = 2 end = 1)
    if (begin < end) {
        //设置枢轴
        long long key = data[begin];
        //设置正向游标
        long long i = begin;
        //设置反向游标
        long long j = end;

        //在子问题里面结束条件是 正向游标大于或等于负向游标，否则这个子问题就是还未解完。
        while (i < j) {

            //如果，正向游标 < 负向游标 并且 负向游标所在位置的值大于枢轴，则负向游标向正向游标前进，结束条件是负向游标查到了第一个小于枢轴的值
            while (i < j && data[j] > key) {
                //上述：负向游标向正向游标前进
                j--;
            }

            //负向游标所指向的值，第一个小于枢轴的值查到后，将其赋给正向游标所指向的值
            // （这时逻辑上，负向游标所指向的值应该设置为空，只不过不做这个操作也不影响逻辑执行结果）
            if (i < j) {
                data[i] = data[j];
                //正向游标向负向游标前进一步
                i++;
            }

            //如果，正向游标 < 负向游标 并且 正向游标所在位置的值小于枢轴，则正向游标向负向游标前进，结束条件是正向游标查到了第一个大于枢轴的值
            while (i < j && data[i] < key) {
                //上述：正向游标向负向游标前进
                i++;
            }

            //正向游标所指向的值，第一个大于枢轴的值查到后，将其赋给负向游标所指向的值
            // （这时逻辑上，正向游标所指向的值应该设置为空，只不过不做这个操作也不影响逻辑执行结果：注意这也就是为什么最后是将枢轴的值赋给i不是赋值给j）
            if (i < j) {
                data[j] = data[i];
                //负向游标向正向游标前进一步
                j--;
            }

        }

        //将枢轴的值赋给 正向游标所指向的值。（此时i+1 = j了） 此时子问题解决
        data[i] = key;
        QuickSortSimple(data, begin, i - 1);
        QuickSortSimple(data, i + 1, end);
    }

}

template<typename T>
void Sort::RadixSort(std::vector<T> &data) {
    std::vector<T> tmp[10];
    int k = 0;
    T max_element = data[0];
    for (int i = 1; i < data.size(); i++) {
        max_element = std::max(max_element, data[i]);
    }
    if (max_element) {
        while (max_element) {
            max_element /= 10;
            k++;
        }
    } else {
        k = 1;
    }
    T x=1;
    for (int i = 1; i <= k; i++, x *= 10) {
        for (int j = 0; j < data.size(); j++) {
            int v = (data[j] / x) % 10;
            tmp[v].push_back(data[j]);
        }
        for (int j = 0, p = 0; j <= 9; j++) {
            for (int l = 0; l < tmp[j].size(); l++) {
                data[p++] = tmp[j][l];
            }
            tmp[j].clear();
        }
    }
}

template<typename T>
/**
 * 希尔排序
 * @tparam T 输入数据类型
 * @param data 输入数据集合
 */
void Sort::ShellSort(std::vector<T> &data) {
    long long n = data.size();
    long long inc;//希尔增量 步长
    //这里采用朴素希尔增量，就是每次增量都是原来的一半，直到增量为1为止
    for (inc = n / 2; inc >= 1; inc = inc / 2) {
        //插入排序
        for (long long i = inc; i < n; i++) {
            long long temp = data[i];//temp存储要插入的值
            long long j;
            //j从i-inc开始往前遍历，每一步的距离是inc
            for (j = i - inc; j >= 0 && data[j] > temp; j = j - inc) {
                data[j + inc] = data[j];
            }
            data[j + inc] = temp;
        }
    }
}

static int single_task_len;

template<typename T>
static void quick_sort_multi_thread_by_async(std::vector<T> &data, int l, int r) {
    if (l < r) {
        std::swap(data[l], data[l + rand() % (r - l + 1)]);
        int bound1 = l, bound2 = r + 1, i = l + 1;
        while (i < bound2) {
            if (data[i] < data[l]) {
                std::swap(data[i], data[++bound1]);
                i++;
            } else if (data[i] > data[l]) {
                std::swap(data[i], data[--bound2]);
            } else {
                i++;
            }
        }
        std::swap(data[l], data[bound1]);
        if (bound1 - l + r - bound2 + 1 > single_task_len) {
            auto res = std::async(quick_sort_multi_thread_by_async<T>, std::ref(data), l, bound1 - 1);
            quick_sort_multi_thread_by_async(data, bound2, r);
            res.get();
        } else {
            quick_sort_multi_thread_by_async(data, l, bound1 - 1);
            quick_sort_multi_thread_by_async(data, bound2, r);
        }
    }
}

template<typename T>
void Sort::QuickSortMultiThreadByAsync(std::vector<T> &data) {
    single_task_len = data.size() / std::thread::hardware_concurrency();
    quick_sort_multi_thread_by_async(data, 0, data.size() - 1);
}

template<typename T>
void Sort::MergeSortMultiThreadByAsync(std::vector<T> &data) {
    std::vector<T> MergeSortBuffer(data.size());
    single_task_len=data.size()/std::thread::hardware_concurrency();
    static std::function<void(int l, int r)> merge_sort = [&data, &MergeSortBuffer](int l, int r) {
        if (l >= r)return;
        int mid = (l + r) / 2;
        if(r-l+1>=single_task_len)
        {
            auto res=std::async(merge_sort,l,mid);
            merge_sort(mid+1,r);
            res.get();
        }
        else
        {
            merge_sort(l, mid);
            merge_sort(mid + 1, r);
        }
        int i = l, j = mid + 1, p = l;
        while (i <= mid && j <= r) {
            if (data[i] > data[j]) {
                MergeSortBuffer[p++] = data[j++];
            } else {
                MergeSortBuffer[p++] = data[i++];
            }
        }
        while (i <= mid) {
            MergeSortBuffer[p++] = data[i++];
        }
        while (j <= r) {
            MergeSortBuffer[p++] = data[j++];
        }
        for (i = l; i <= r; i++) {
            data[i] = MergeSortBuffer[i];
        }
    };
    if (MergeSortBuffer.size() < data.size()) {
        MergeSortBuffer.resize(data.size());
    }
    merge_sort(0, data.size() - 1);
}




#endif //BUAA_PROGRAMMINGANDALGORITHMS_TERMPROJECT_SORT_H
