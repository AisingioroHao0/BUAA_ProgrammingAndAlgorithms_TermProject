#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include "Sort.h"
#include "HighPrecisionNumber.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/time.h>
#include <pthread.h>
#include <algorithm>
using namespace std;
template<typename T>
const long MAX = 1e7L; // max num in array
const long long MAX_NUM = 1e8L;  // num of element to sort
const int thread = 100;
const int thread_num = MAX_NUM / thread;

int num[MAX_NUM];
int tmp_num[MAX_NUM];

pthread_barrier_t barrier;  // barrier

void init()//HJZ 2022-11-8
{
    srand(1);
    for (int i = 0; i < MAX_NUM; ++i) {
        num[i] = rand() % MAX;
    }
}

void quicksorts(int* start, int* end) { //editor:hjz 2022-11-8
    int nums = end - start;
    if (nums > 0) {
        int flag = start[0];
        int i = 0;
        int j = nums;
        while (i < j) {
            while (j > i && start[j] > flag) {
                --j;
            }
            start[i] = start[j];
            while (i < j && start[i] <= flag) {
                ++i;
            }
            start[j] = start[i];
        }
        start[i] = flag;
 
        quicksorts(start, start + i - 1);
        quicksorts(start + i + 1, end);
    }
}

void* work(void* arg) { //hjz 2022-11-8
    long index = (long long)arg;
    quicksorts(num+index, num+index+thread_num-1);
    pthread_barrier_wait(&barrier);
    pthread_exit(NULL);
}

void merge() //hjz 2022-11-8
{
    long index[thread];
    for (int i = 0; i < thread; ++i)
    {
        index[i] = i * thread_num;
    }
 
    for(long i = 0; i < MAX_NUM; ++i)
    {
        long min_index;
        long min_num = MAX;
        for(int j = 0; j < thread; ++j)
        {
            if((index[j] < (j + 1) * thread_num)
                && (num[index[j]] < min_num))
            {
                min_index = j;
                min_num = num[index[j]];
            }
        }
        tmp_num[i] = num[index[min_index]];
        index[min_index]++;
    }
}


bool Judge(vector<T> &data)
{
    for(int i=0;i<data.size()-1;i++)
    {
        if(data[i]>data[i+1])
        {
            return false;
        }
    }
    return true;
}
void TestSort(int n,function<void(vector<long long>&)> sort_function)
{
    vector<long long > test_data(n);
    static default_random_engine random_engine;
    static uniform_int_distribution<long long> random_range(LONG_LONG_MIN, LONG_LONG_MAX);
    for(int i=0;i<n;i++)
    {

        test_data[i]=random_range(random_engine);
    }
    sort_function(test_data);
    cout<<Judge(test_data);
}
void TestHighPrecisionNumber(int n)
{
    static default_random_engine random_engine;
    static uniform_int_distribution<int> random_len(1, 100);
    static uniform_int_distribution<int> random_digit(0, 9);
    static uniform_int_distribution<int> random_is_positive(0, 1);
    vector<HighPrecisionNumber> test_data(n);
    ofstream out_stream("HighPrecisionNumbers.txt",ios::out);
    for(int i=0;i<n;i++)
    {
        int len=random_len(random_engine);
        int is_positive=random_is_positive(random_engine);
        string res;
        if(is_positive)
        {
            res.push_back('-');
        }
        while(1)
        {
            int x=random_digit(random_engine);
            if(x)
            {
                res.push_back(x+'0');
                break;
            }
        }
        for(int i=2;i<=len;i++)
        {
            res.push_back(random_digit(random_engine)+'0');
        }
        len=random_len(random_engine);
        if(len)
        {
            res.push_back('.');
            for(int i=1;i<=len;i++)
            {
                res.push_back(random_digit(random_engine)+'0');
            }
        }
        test_data[i]=res;
        out_stream<<res<<'\n';
    }
    out_stream.close();
    Sort<HighPrecisionNumber>::MergeSort(test_data);
    cout<<Judge(test_data);
}

//int main() {
  //  TestHighPrecisionNumber(1e6);
//}

int main(int argc, char *argv[]) //hjz 2022-11-8
{
    init();
    struct timeval start, end;
    pthread_t ptid;
    printf("%ld %ld\n", num[1], num[2]);
    gettimeofday(&start, NULL);
    //init pthread and thread barrier
    pthread_barrier_wait(&barrier);
    //add 1, total have (thread+1) threads
    for (int i = 0; i < thread; ++i) {
        pthread_create(&ptid, NULL, work, (void*)(i*thread_num));
    }
    pthread_barrier_wait(&barrier);
    merge();
    gettimeofday(&end, NULL);
    long long s_usec = start.tv_sec * 1000000 + start.tv_usec;
    long long e_usec = end.tv_sec * 1000000 + end.tv_usec;
 
    double useTime = (double)(e_usec - s_usec) / 1000000.0;
    printf("sort use %.4f seconds\n", useTime);
 
 
 
    return 0;
}