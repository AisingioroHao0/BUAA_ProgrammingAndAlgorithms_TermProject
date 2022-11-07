#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include "Sort.h"
#include "HighPrecisionNumber.h"
using namespace std;
template<typename T>
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
int main() {
    TestHighPrecisionNumber(1e6);
}
