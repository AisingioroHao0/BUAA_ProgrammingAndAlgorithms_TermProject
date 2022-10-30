#include <iostream>
#include <vector>
#include "Sort.h"
#include "HighPrecisionNumber.h"
using namespace std;
void GenerateData(vector<int> &data,int n)
{
    if(data.size()<n)
    {
        data.resize(n);
    }
    for(int i=0;i<n;i++)
    {
        data[i]=rand();
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
vector<int> TestData;
int main() {
    GenerateData(TestData,1e6);
    Sort<int>::RadixSort(TestData);
    cout<<Judge(TestData);
}
