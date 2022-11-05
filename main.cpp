#include <iostream>
#include <vector>
#include <random>
#include "Sort.h"
#include "HighPrecisionNumber.h"
using namespace std;
void GenerateData(vector<long long> &data,int n)
{
    if(data.size()<n)
    {
        data.resize(n);
    }
    static default_random_engine random_engine;
    static uniform_int_distribution<long long> random_range(LONG_LONG_MIN, LONG_LONG_MAX);
    for(int i=0;i<n;i++)
    {
        data[i]=random_range(random_engine);
    }
}
template<typename T>
bool Judge(vector<T> data)
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
vector<long long> TestData;
int main() {
    GenerateData(TestData,1e5);
    Sort<long long>::MergeSort(TestData);
    cout<<Judge(TestData);
}
