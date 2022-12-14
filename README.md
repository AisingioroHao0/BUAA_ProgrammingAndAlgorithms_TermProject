# BUAA_ProgrammingAndAlgorithms_TermProject

## 分工

- 艾昊
  - 三路随机快速排序
  - 基数排序
  - 归并排序
  - 高精度实现，高精度排序
  - 分布式快速排序
  - 分布式归并排序

- 何金泽
  - 分布式外部排序

- 徐龙
  - 选择排序
  - 希尔排序
  - 二路快速排序
  - Java实现分布式快速排序
  - 分布式（多节点）排序分析
    

## 对比

| 排序种类\数据规模   | 1e5     | 1e6       | 1e7    | 1e8      | 1e9      |
|-------------| ------- |-----------| ------ | -------- | :------- |
| 选择排序        | 20650ms | 2141159ms | 太长   | 太长     |          |
| 归并排序        | 36ms    | 849ms     | 5002ms | 63826ms  |          |
| 简单快速排序      | 14ms    | 223ms     | 2037ms | 26698ms  |          |
| 希尔排序        | 38ms    | 575ms     | 8250ms | 152216ms |          |
| 基数排序        | 50ms    | 523ms     | 4896ms | 48730ms  |          |
| 三路快速排序      |         | 396ms     | 4635ms | 53719ms  | 594666ms |
| 分布式快速排序     | 9ms | 102ms     | 831ms  | 8874ms   | 104291ms |
| 分布式归并排序     | 9ms | 83ms      | 729ms  | 7448ms   | 77042ms  |
| 分布式排序+多路归并 | 41ms | 410ms | 4076ms |  |  |
| Java分布式快速排序 | 16ms | 56ms      | 636ms  | 7572ms   |          |


## 基础排序

### 对比图

| 排序种类\数据规模 | 1e5 | 1e6       | 1e7    | 1e8      | 1e9      |
|-----------| --- |-----------|--------|----------| -------- |
| 选择排序      | 20650ms | 2141159ms | 太长     | 太长       |  |
| 归并排序      | 36ms | 849ms     | 5002ms | 63826ms  |  |
| 简单快速排序    |14ms| 223ms     | 2037ms | 26698ms  |          |
| 希尔排序      | 38ms| 575ms     | 8250ms | 152216ms |          |
| 基数排序      | 50ms| 523ms     | 4896ms | 48730ms  |          |

1e5
![img_7.png](README.assets/img_7.png)

1e6
![img_8.png](README.assets/img_8.png)

1e7
![img_9.png](README.assets/img_9.png)

1e8
![img_10.png](README.assets/img_10.png)

### 基础排序算法分析

#### 简单选择排序
简单选择排序
基本思想：比较+交换
1. 从待排序序列中，找到关键字最小的元素；
2. 如果最小元素不是待排序序列的第一个元素，将其和第一个元素互换；
3. 从余下的 N - 1 个元素中，找出关键字最小的元素，重复(1)、(2)步，直到排序结束。
   简单选择排序通过两层循环实现。
   第一层循环：依次遍历序列当中的每一个元素
   第二层循环：将遍历得到的当前元素依次与余下的元素进行比较，符合最小元素的条件，则交换。
   ![selectionSort](README.assets/selectionSort.gif)
   总的时间复杂度为O(n^2)


#### 归并排序
归并排序算法实现排序的思路是：
1. 将整个待排序序列划分成多个不可再分的子序列，每个子序列中仅有 1 个元素；
2. 所有的子序列进行两两合并，合并过程中完成排序操作，最终合并得到的新序列就是有序序列。

举个简单的例子，使用归并排序算法对 {7, 5, 2, 4, 1, 6, 3, 0} 实现升序排序的过程是：
1) 将 {7, 5, 2, 4, 1, 6, 3, 0} 分割成多个子序列，每个子序列中仅包含 1 个元素，分割过程如下所示：
   ![归并分](README.assets/归并分.png)
   整个序列不断地被一分为二，最终被分割成 {7}、{5}、{2}、{4}、{1}、{6}、{3}、{0} 这几个序列。
2) 将 {7}、{5}、{2}、{4}、{1}、{6}、{3}、{0} 以“两两合并”的方式重新整合为一个有序序列，合并的过程如下图所示：
   ![归并治](README.assets/归并治.png)

其时间复杂度为
O(nlogn)

#### 快速排序
快速排序是对冒泡排序的一种改进，由 C.A.R.Hoare（Charles Antony Richard Hoare，东尼·霍尔）在 1962 年提出。

快速排序的基本思想是：**通过一趟排序将要排序的数据分割成独立的两部分，其中一部分的所有数据比另一部分的所有数据要小，再按这种方法对这两部分数据分别进行快速排序，整个排序过程可以递归进行，使整个数据变成有序序列。
排序算法的思想非常简单。**

1. 在待排序的数列中，我们首先要找一个数字作为基准数（这只是个专用名词）。为了方便，我们一般选择第 1 个数字作为基准数（其实选择第几个并没有关系）。
2. 接下来我们需要把这个待排序的数列中小于基准数的元素移动到待排序的数列的左边，把大于基准数的元素移动到待排序的数列的右边。这时，左右两个分区的元素就相对有序了；
3. 接着把两个分区的元素分别按照上面两种方法继续对每个分区找出基准数，然后移动，直到各个分区只有一个数时为止。

这是典型的分治思想，即分治法。（先治后分，代码中对简单快速排序有逐行详细解释）

其最好时间复杂度为 O(nlogn) 最坏时间复杂度为 O(n2)
一个例子： 数列 47、29、71、99、78、19、24、47
进行第 1 趟第 1 个交换的排序情况如下
![img.png](README.assets/img.png)
交换之后，j 移动到了下标为 6 的位置，对 i 继续扫描，如图 2 所示
![img_1.png](README.assets/img_1.png)
此时交换后的数列变为 24、29、47、99、78、19、71、47。接下来我们继续对 i、j 进行操作，如图 3 所示，继续进行 i-- 及 j++ 的比较操作
![img_2.png](README.assets/img_2.png)

#### 希尔排序
希尔排序(Shell Sort)是插入排序的一种。也称缩小增量排序，是直接插入排序算法的一种更高效的改进版本。
希尔排序，是一种非稳定的更高效的插入排序，在对几乎已经排好序的数据操作时，效率极高，即可以达到线性排序的效率，直接插入排序整体来说是低效的，因为插入排序每次只能将数据移动一位；

希尔排序的基本思想是：先将整个待排序的记录序列分割成为若干子序列分别进行直接插入排序，待整个序列中的记录“基本有序”时，再对全体记录进行依次直接插入排序。

过程如下：

1. 选择一个增量序列 t1，t2，……，tk，其中 ti > tj, tk = 1；

2. 按增量序列个数 k，对序列进行 k 趟排序；

3. 每趟排序，根据对应的增量 ti，将待排序列分割成若干长度为 m 的子序列，分别对各子表进行直接插入排序。仅增量因子为 1 时，整个序列作为一个表来处理，表长度即为整个序列的长度。
最好情况：O(n)
最坏情况：O(n^2)


![img_3.png](README.assets/img_3.png)

#### 基数排序
基数排序不同于之前所介绍的各类排序，前边介绍到的排序方法或多或少的是通过使用比较和移动记录来实现排序，而基数排序的实现不需要进行对关键字的比较，只需要对关键字进行“分配”与“收集”两种操作即可完成。

例如对无序表{50，123，543，187，49，30，0，2，11，100}进行基数排序，由于每个关键字都是整数数值，且其中的最大值由个位、十位和百位构成，每个数位上的数字从 0 到 9，首先将各个关键字按照其个位数字的不同进行分配分配表如下图所示

![img_4.png](README.assets/img_4.png)


通过按照各关键字的个位数进行分配，按照顺序收集得到的序列变为：{50，30，0，100，11，2，123，543，187，49}。在该序列表的基础上，再按照各关键字的十位对各关键字进行分配，得到的分配表如下图所示：

![img_5.png](README.assets/img_5.png)

由上表顺序收集得到的记录表为：{0、100、2、11、123、30、543、49、50、187}。在该无序表的基础上，依次将表中的记录按照其关键字的百位进行分配，得到的分配如下图所示：

![img_6.png](README.assets/img_6.png)

最终通过三次分配与收集，最终得到的就是一个排好序的有序表：{0、2、11、30、49、50、100、123、187、543}。
例子中是按照个位-十位-百位的顺序进行基数排序，此种方式是从最低位开始排序，所以被称为最低位优先法（简称“LSD法”）。
同样还可以按照百位-十位-各位的顺序进行排序，称为最高位优先法（简称“MSD法”）。

对于给定的n个d位数，取值范围为[0,k]，我们使用计数排序比较元素的每一位，基数排序耗时Θ(n+k)，那么基数排序的复杂度为Θ(d(n+k))。

## 高精度排序

### 核心思想

利用两个字符串存储高精度数字，一个字符串存储小数，一个字符串存储整数，一个bool值标识正负，重载运算符，使其兼容排序算法。

```cpp
class HighPrecisionNumber {
    bool is_positive= true;
    std::string interger,decimal;
public:
    HighPrecisionNumber(){}
    HighPrecisionNumber(const std::string& x) {
        int l = 0, r = x.size() - 1;
        if (x.size() && x[0] == '-') {
            is_positive = false;
            l = 1;
        }
        for (int i = l; i <= r; i++) {
            if (x[i] == '.') {
                interger = x.substr(l, i - l);//i-1-l+1
                decimal = x.substr(i + 1, r - i);//r-(i+1)+1
                break;
            }
        }
        if (interger.empty() && decimal.empty()) {
            interger = x.substr(l, r - l + 1);
        }
    }
    bool operator >(const HighPrecisionNumber& x)const {
        if (is_positive && !x.is_positive) {
            return true;
        }
        if (!is_positive && x.is_positive) {
            return false;
        }
        bool res;
        if (interger.size() > x.interger.size()) {
            res = true;
        } else if (interger.size() < x.interger.size()) {
            res = false;
        } else {
            if (interger > x.interger) {
                res = true;
            } else if (interger < x.interger) {
                res = false;
            } else {
                for (int i = 0; i < decimal.size(); i++) {
                    if (i < x.decimal.size()) {
                        if (decimal[i] > x.decimal[i]) {
                            res = true;
                            break;
                        } else if (decimal[i] < x.decimal[i]) {
                            res = false;
                            break;
                        }
                    } else {
                        res = true;
                        break;
                    }
                }
                return false;
            }
        }
        if (!is_positive) {
            res = !res;
        }
        return res;
    }
};
```

### 实验结果

- 分布式归并排序，1e6数据，101位整数，101位小数

  ![image-20221121213127207](README.assets/image-20221121213127207.png)

## 分布式排序

### 对比图

| 排序种类\数据规模 | 1e6   | 1e7    | 1e8     | 1e9      |
| ----------------- | ----- | ------ | ------- | -------- |
| 三路快速排序      | 396ms | 4635ms | 53719ms | 594666ms |
| 分布式快速排序    | 102ms | 831ms  | 8874ms  | 104291ms |
| 分布式归并排序    | 83ms  | 729ms  | 7448ms  | 77042ms  |

### 核心思想

根据当前的硬件最高并发线程数，计算出每个线程应处理的数据规模，每个任务节点判断当前处理的规模是否有必要划分新的线程解决子任务。

若硬件并发数为4，线程执行函数图应如下所示，更多的线程可依此类推。

![image-20221121205324213](README.assets/image-20221121205324213.png)

### 分布式快速排序

#### 核心代码

```cpp
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
```

#### 实验结果

- 1e6

  ![image-20221115000245982](README.assets/image-20221115000245982.png)

- 1e7

  ![image-20221114233724776](README.assets/image-20221114233724776.png)

- 1e8

  ![image-20221121213332516](README.assets/image-20221121213332516.png)

- 1e9

  ![image-20221115000051316](README.assets/image-20221115000051316.png)

### 分布式归并排序

#### 核心代码

```cpp
template<typename T>
void Sort::MergeSortMultiThreadByAsync(std::vector<T> &data) {
    std::vector<T> MergeSortBuffer(data.size());
    single_task_len = data.size() / std::thread::hardware_concurrency();
    static std::function<void(int l, int r)> merge_sort = [&data, &MergeSortBuffer](int l, int r) {
        if (l >= r)return;
        int mid = (l + r) / 2;
        if (r - l + 1 >= single_task_len) {
            auto res = std::async(merge_sort, l, mid);
            merge_sort(mid + 1, r);
            res.get();
        } else {
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
```

#### 实验结果

- 1e6

  ![image-20221121202901089](README.assets/image-20221121202901089.png)

- 1e7

  ![image-20221121195501270](README.assets/image-20221121195501270.png)

- 1e8

  ![image-20221121194611442](README.assets/image-20221121194611442.png)

- 1e9

  ![image-20221121193400661](README.assets/image-20221121193400661.png)

### 外部排序（败者树）
败者树：胜者树和败者树都是完全二叉树，是树形选择排序的一种变型。每个叶子结点相当于一个选手，每个中间结点相当于一场比赛，每一层相当于一轮比赛。
不同的是，胜者树的中间结点记录的是胜者的标号；而败者树的中间结点记录的败者的标号。
胜者树与败者树可以在log(n)的时间内找到最值。任何一个叶子结点的值改变后，利用中间结点的信息，还是能够快速地找到最值。在k路归并排序中经常用到。
![img0.png](README.assets/img0.png)
叶子节点相当于参赛选手，中间节点是比赛，比赛中败者记录在中间节点，胜者继续参加后面的比赛，直到根节点。根节点之上的一个节点用来记录最终胜者。

败者树的建立：在参赛者数组b[]的最后添加一位，存放一个参赛选手的绝对最小值（选手都是正数的话，如-1）。所有中间节点都记录这个最小值的下标。然后依次调整（adjust()）各个选手即可。

败者树的调整：当改变一个选手的值，需要调整以维持败者树的形态。败者树只需调整选手的父节点即可。当子节点的值大于父节点，则子节点记录于父节点（小为胜利，记录败者），父节点继续与其父节点比赛；若子节点小于父节点，则直接使用子节点进行下一轮比赛。

本算法的流程：
假设文件中整数个数为N(N是亿级的)，整数之间用空格分开。首先分多次从该文件中读取M（十万级）个整数，每次将M个整数在内存中使用快速排序之后存入临时文件，然后使用多路归并将各个临时文件中的数据再次整体排好序后存入输出文件。显然，该排序算法需要对每个整数做2次磁盘读和2次磁盘写。以下是本程序的流程图：
对比图：
![img_1_1.png](README.assets/img_1_1.png)
![img_2_2.png](README.assets/img_2_2.png)


| 排序种类\排序规模       | 1e5     | 1e6       | 1e7    | 1e8     |
| ----------------------- | ------- | --------- | ------ | ------- |
| 归并排序                | 36ms    | 849ms     | 5002ms | 63826ms |
| 外部排序（归并+败者树） | 326     | 3914      | 33183  | 227857  |
| 选择排序                | 20650ms | 2141159ms | 太长   | 太长    |
|                         |         |           |        |         |


效果测试：
![img_71.png](README.assets/img_71.png)
![img_111.png](README.assets/img_111.png)
![img_91.png](README.assets/img_91.png)
![img_101.png](README.assets/img_101.png)

#### 核心代码
![img_121.png](README.assets/img_121.png)
![img_13.png](README.assets/img_13.png)
![img_13.png](README.assets/img_14.png)
![img_13.png](README.assets/img_15.png)
![img_13.png](README.assets/img_16.png)
![img_13.png](README.assets/img_17.png)

### Java实现分布式快速排序
#### 原因分析
Java在大家的常看到的文章里面，执行的速度是很慢的，比不过c++，这个说的是比较对的。
具体到实际的应用里面，还是要看场景，和代码能力的。

我们组c++实现的多线程排序对CPU的占用，随时间变化如下。
![img_11.png](README.assets/img_11.png)
而使用Java，JUC（Doug Lea，道格利大师）提供的线程池，间接的去操作内核线程，在底层使用了c++、
c、和汇编语言，对并发性能提供了支持。
体现在CPU的利用率上就是，开始排序的时候利用率达到了70%逐渐降低到40%，从40%再突然结束CPU使用。
![img_12.png](README.assets/img_12.png)


#### 实现结果
CPU核心数 8
第0轮并发快排，数据量 10000000 耗时（毫秒） 349

CPU核心数 8
第1轮并发快排，数据量 10000000 耗时（毫秒） 373

CPU核心数 8
第2轮并发快排，数据量 10000000 耗时（毫秒） 606

CPU核心数 8
第3轮并发快排，数据量 10000000 耗时（毫秒） 455

CPU核心数 8
第4轮并发快排，数据量 10000000 耗时（毫秒） 467

CPU核心数 8
第5轮并发快排，数据量 10000000 耗时（毫秒） 468

CPU核心数 8
第6轮并发快排，数据量 10000000 耗时（毫秒） 437

CPU核心数 8
第7轮并发快排，数据量 10000000 耗时（毫秒） 496

CPU核心数 8
第8轮并发快排，数据量 10000000 耗时（毫秒） 427

CPU核心数 8
第9轮并发快排，数据量 10000000 耗时（毫秒） 783

CPU核心数 8
第10轮并发快排，数据量 10000000 耗时（毫秒） 463

CPU核心数 8
第11轮并发快排，数据量 10000000 耗时（毫秒） 401

CPU核心数 8
第12轮并发快排，数据量 10000000 耗时（毫秒） 468

CPU核心数 8
第13轮并发快排，数据量 10000000 耗时（毫秒） 720

CPU核心数 8
第14轮并发快排，数据量 10000000 耗时（毫秒） 480

CPU核心数 8
第15轮并发快排，数据量 10000000 耗时（毫秒） 379

CPU核心数 8
第16轮并发快排，数据量 10000000 耗时（毫秒） 463

CPU核心数 8
第17轮并发快排，数据量 10000000 耗时（毫秒） 417

CPU核心数 8
第18轮并发快排，数据量 10000000 耗时（毫秒） 477

CPU核心数 8
第19轮并发快排，数据量 10000000 耗时（毫秒） 448

===============================================================

CPU核心数 8
第0轮并发快排，数据量 100000000 耗时（毫秒） 5927

CPU核心数 8
第1轮并发快排，数据量 100000000 耗时（毫秒） 7583

CPU核心数 8
第2轮并发快排，数据量 100000000 耗时（毫秒） 7572

CPU核心数 8
第3轮并发快排，数据量 100000000 耗时（毫秒） 5332

CPU核心数 8
第4轮并发快排，数据量 100000000 耗时（毫秒） 5548

CPU核心数 8
第5轮并发快排，数据量 100000000 耗时（毫秒） 6190

CPU核心数 8
第6轮并发快排，数据量 100000000 耗时（毫秒） 4215

CPU核心数 8
第7轮并发快排，数据量 100000000 耗时（毫秒） 6877

CPU核心数 8
第8轮并发快排，数据量 100000000 耗时（毫秒） 5972

CPU核心数 8
第9轮并发快排，数据量 100000000 耗时（毫秒） 5584

CPU核心数 8
第10轮并发快排，数据量 100000000 耗时（毫秒） 5187

CPU核心数 8
第11轮并发快排，数据量 100000000 耗时（毫秒） 5206

CPU核心数 8
第12轮并发快排，数据量 100000000 耗时（毫秒） 5769

CPU核心数 8
第13轮并发快排，数据量 100000000 耗时（毫秒） 5181

CPU核心数 8
第14轮并发快排，数据量 100000000 耗时（毫秒） 4588

CPU核心数 8
第15轮并发快排，数据量 100000000 耗时（毫秒） 7043

CPU核心数 8
第16轮并发快排，数据量 100000000 耗时（毫秒） 8202

CPU核心数 8
第17轮并发快排，数据量 100000000 耗时（毫秒） 5632

CPU核心数 8
第18轮并发快排，数据量 100000000 耗时（毫秒） 6263

CPU核心数 8
第19轮并发快排，数据量 100000000 耗时（毫秒） 5841

