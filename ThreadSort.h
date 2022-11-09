//
//edited by HJZ 2022-11-9
//
#ifndef BUAA_PROGRAMMINGANDALGORITHMS_TERMPROJECT_HIGHPRECISIONNUMBER_H
#define BUAA_PROGRAMMINGANDALGORITHMS_TERMPROJECT_HIGHPRECISIONNUMBER_H
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <sys/time.h>
#include <pthread.h>
#include <algorithm>
#include <ThreadPool.h>

class ThreadSort{
    ThreadSort(){}
    ThreadSort(int argc, char *argv[])
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
    public:
    void quicksorts(int* start, int* end)
    void merge()
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
    void* work(void* arg)
    {
    long index = (long long)arg;
    quicksorts(num+index, num+index+thread_num-1);
    pthread_barrier_wait(&barrier);
    pthread_exit(NULL);
    }
    void init()
{
    srand(1);
    for (int i = 0; i < MAX_NUM; ++i) {
        num[i] = rand() % MAX;
    }
}

}