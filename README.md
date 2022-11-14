# buaa_ProgrammingAndAlgorithms_TermProject

## 分布式排序

### 对比图

| 排序种类\数据规模                     | 1e5  | 1e6   | 1e7    | 1e8     | 1e9      |
| ------------------------------------- | ---- | ----- | ------ | ------- | -------- |
| 普通快速排序                          | 33ms | 396ms | 4635ms | 53719ms | 594666ms |
| 无锁分布式快速排序，基于future与async | 11ms | 102ms | 831ms  | 9594ms  | 104291ms |
|                                       |      |       |        |         |          |

### 无锁分布式快速排序

#### 实验结果

- 1e5

  ![image-20221115000222836](README.assets/image-20221115000222836.png)

- 1e6

  ![image-20221115000245982](README.assets/image-20221115000245982.png)

- 1e7

  ![image-20221114233724776](README.assets/image-20221114233724776.png)

- 1e8

  ![image-20221114234145665](README.assets/image-20221114234145665.png)

- 1e9

  ![image-20221115000051316](README.assets/image-20221115000051316.png)
