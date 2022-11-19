#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <fstream>
#include "Sort.h"
#include <ctime>
#include <fstream>
#include "HighPrecisionNumber.h"
#include <algorithm>
#include "ExternSort.h"
const unsigned int Fcount = 10000000; // 文件里数据的行数
const unsigned int number_to_sort = 1000000; //在内存中一次排序的数量
const char *unsort_file = "unsort_data.txt"; //原始未排序的文件名
const char *sort_file = "sort_data.txt"; //已排序的文件名
void init_data(unsigned int num); //随机生成数据文件
void init_data(unsigned int num)
{
    FILE* f = fopen(unsort_file, "wt");
    for(int i = 0; i < num; ++i)
        fprintf(f, "%d ", rand());
    fclose(f);
}
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

template<typename T>
void TestSort(int n,function<void(vector<T>&)> sort_function)
{
    vector<long long > test_data(n);
    static default_random_engine random_engine;
    static uniform_int_distribution<long long> random_range(LONG_LONG_MIN, LONG_LONG_MAX);
    for(int i=0;i<n;i++)
    {
        test_data[i]=random_range(random_engine);
    }
    auto start_time=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    sort_function(test_data);
    auto end_time=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    cout<<"time cost:"<<end_time-start_time<<"ms"<<'\n';
    cout<<Judge(test_data)<<'\n';
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
    Sort::MergeSort(test_data);
    cout<<Judge(test_data)<<'\n';
}

int main() {
//    cout<<"hardware_concurrency:"<<thread::hardware_concurrency()<<'\n';
//    TestSort<long long>(1e6,Sort::QuickSort<long long>);
//    TestSort<long long>(1e6, Sort::MultiThreadQuickSortByAsync<long long>);
//    TestSort<long long>(1e6,Sort::QuickSortForSimple<long long>);
    srand(time(NULL));
    init_data(Fcount);
    ExternSort extSort(unsort_file, sort_file, number_to_sort);
    extSort.sort();
    system("pause");
    return 0;
}

