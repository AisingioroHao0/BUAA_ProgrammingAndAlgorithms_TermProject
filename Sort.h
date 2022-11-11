//
// Created by AisingioroHao on 2022/10/29.
//

#ifndef BUAA_PROGRAMMINGANDALGORITHMS_TERMPROJECT_SORT_H
#define BUAA_PROGRAMMINGANDALGORITHMS_TERMPROJECT_SORT_H

#include <vector>
#include <functional>
#include <thread>
#include <future>


class Sort {
public:
    template<typename T>
    static void SelectionSort(std::vector<T> &data);

    template<typename T>
    static void MergeSort(std::vector<T> &data);

    template<typename T>
    static void QuickSort(std::vector<T> &data);

    template<typename T>
    static void ShellSort(std::vector<T> &data);

    template<typename T>
    static void RadixSort(std::vector<T> &data);

    template<typename T>
    static void MultiThreadQuickSortByAsync(std::vector<T> &data);
    template<typename T>
    static void MultiThreadMergeSortByAsync(std::vector<T> &data);
};

template<typename T>
/**
 * 选择排序
 * @tparam T 传入数据类型
 * @param data 传入的数据集合
 */
void Sort::SelectionSort(std::vector<T> &data) {
    int n = data.size();
    for (int i = 0; i < n - 1; i++) {
        //当前趟最小元素下标
        int min = i;
        //寻找当前趟的最小元素，并将最小元素的下标赋值给min
        for (int j = i + 1; j < n; j++) {
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
    static std::function<void(int l, int r)> merge_sort = [&data,&MergeSortBuffer](int l, int r) {
        if (l >= r)return;
        int mid = (l + r) / 2;
        merge_sort(l, mid);
        merge_sort(mid + 1, r);
        int i = l, j = mid + 1, p = l;
        while (i <= mid && j <= r) {
            if(data[i]>data[j])
            {
                MergeSortBuffer[p++] = data[j++];
            }
            else {
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
static void quick_sort(std::vector<T> &data,int l,int r)
{
    if(l>=r)return;
    std::swap(data[l],data[l+rand()%(r-l+1)]);
    int bound1=l,bound2=r+1,i=l+1;
    while(i<bound2)
    {
        if(data[i]<data[l])
        {
            std::swap(data[i],data[++bound1]);
            i++;
        }
        else if(data[i]>data[l])
        {
            std::swap(data[i],data[--bound2]);
        }
        else
        {
            i++;
        }
    }
    std::swap(data[l],data[bound1]);
    quick_sort(data,l,bound1-1);
    quick_sort(data,bound2,r);
}
template<typename T>
void Sort::QuickSort(std::vector<T> &data) {
    quick_sort(data,0,data.size()-1);
}

template<typename T>
void Sort::RadixSort(std::vector<T> &data) {
    std::vector<int> tmp[10];
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
    for (int i = 1, x = 1; i <= k; i++, x *= 10) {
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
    int n = data.size();
    int inc;//希尔增量 步长
    //这里采用朴素希尔增量，就是每次增量都是原来的一半，直到增量为1为止
    for (inc = n / 2; inc >= 1; inc = inc / 2) {
        //插入排序
        for (int i = inc; i < n; i++) {
            int temp = data[i];//temp存储要插入的值
            int j;
            //j从i-inc开始往前遍历，每一步的距离是inc
            for (j = i - inc; j >= 0 && data[j] > temp; j = j - inc) {
                data[j + inc] = data[j];
            }
            data[j + inc] = temp;
        }
    }
}
template<typename T>
static void multi_thread_quick_sort_by_async(std::vector<T> &data,int l,int r) {
    if(l>=r)return;
    std::swap(data[l],data[l+rand()%(r-l+1)]);
    int bound1=l,bound2=r+1,i=l+1;
    while(i<bound2)
    {
        if(data[i]<data[l])
        {
            std::swap(data[i],data[++bound1]);
            i++;
        }
        else if(data[i]>data[l])
        {
            std::swap(data[i],data[--bound2]);
        }
        else
        {
            i++;
        }
    }
    std::swap(data[l],data[bound1]);
    auto res1=std::async(std::launch::deferred | std::launch::async,multi_thread_quick_sort_by_async<T>,std::ref(data),l,bound1-1);
    auto res2=std::async(std::launch::deferred | std::launch::async,multi_thread_quick_sort_by_async<T>,std::ref(data),bound2,r);
    res1.get();
    res2.get();
}
template<typename T>
void Sort::MultiThreadQuickSortByAsync(std::vector<T> &data) {
    auto res=std::async(std::launch::async,multi_thread_quick_sort_by_async<T>,std::ref(data), 0, data.size() - 1);
    res.get();
}

template<typename T>
void Sort::MultiThreadMergeSortByAsync(std::vector<T> &data){
    auto res=std::async(std::launch::async,multi_thread_merge_sort_by_async<T>,std::ref(data), 0, data.size() - 1);
    res.get();
}
template<typename T>
static void multi_thread_merge_sort_by_async(std::vector<T> &data,int l,int r){
    if(l<r){
        int mid=(l+r)/2;
        multi_thread_merge_sort_by_async(data,l,mid);
        multi_thread_merge_sort_by_async(data,mid+1,r);
        merge(data,l,mid,r);
    }
}
template<typename T>
static void merge(std::vector<T>&data,int l,int mid,int r){
    int i=l,j=mid+1,k=0; //mid+1为第2有序区第1个元素，j指向第1个元素
    int *temp=new(nothrow) int[r-l+1]; //temp数组暂存合并的有序序列
    if(!temp){ //内存分配失败
        cout<<"error";
        return;
    }
    while(i<=mid&&j<=r){
        if(data[i]<=data[j]) //较小的先存入temp中
            temp[k++]=data[i++];
        else
            temp[k++]=data[j++];
    }
    while(i<=mid)//若比较完之后，第一个有序区仍有剩余，则直接复制到t数组中
        temp[k++]=data[i++];
    while(j<=high)//同上
        temp[k++]=data[j++];
    for(i=low,k=0;i<=high;i++,k++)//将排好序的存回arr中low到high这区间
		data[i]=temp[k];
    delete []temp;//删除指针，由于指向的是数组，必须用delete []
}

template<typename T>
void Sort::MultiThreadShellSortByAsync(std::vector<T> &data)
{
    auto res=std::async(std::launch::async,multi_thread_shell_sort_by_async<T>,std::ref(data), 0, data.size() - 1);
    res.get();
}
template<typename T>
static void multi_thread_shell_sort_by_async(std::vector<T> &data,int n)
{
    int i,j,gap;   // gap为步长，每次减为原来的一半。
    for (gap = n / 2; gap > 0; gap /= 2)
    {
        // 共gap个组，对每一组都执行直接插入排序
        for (i = 0 ;i < gap; i++)
        {
            for (j = i + gap; j < n; j += gap) 
            { 
                
                if (data[j] < data[j - gap])
                {
                    int tmp = data[j];
                    int k = j - gap;
                    while (k >= 0 && data[k] > tmp)
                    {
                        data[k + gap] = data[k];
                        k -= gap;
                    }
                    data[k + gap] = tmp;
                }
            }
        }
    }
}

#endif //BUAA_PROGRAMMINGANDALGORITHMS_TERMPROJECT_SORT_H
