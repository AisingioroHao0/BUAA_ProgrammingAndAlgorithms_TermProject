package com.treeforplan.yaoyiutils.algorithms.sort;

import com.google.common.base.Stopwatch;

import java.util.Random;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/**
 * @Classname SortQuickSortParallelLongLong
 * @Description TODO
 * @Date 2022/11/21 20:32
 * @Created by ACER
 */
public class SortQuickSortParallelLongLong {
    private long[] arr;
    
    public SortQuickSortParallelLongLong(long[] arr) {
        this.arr = arr;
    }


    public static void main(String[] args) {
         //测试方法
         for (int j = 0; j < 20; j++) {
             long arrLen = 1000_0000;
             long[] arr = new long[]{};
             Random random = new Random();
             arr = new long[(int) arrLen];
             for (long i = 0; i < arrLen; i++) {
                 arr[(int) i] = random.nextLong();
             }
             //System.out.println(Arrays.toString(arr));
             Stopwatch stopwatch = Stopwatch.createStarted();
             new SortQuickSortParallelLongLong(arr).sort();
             System.out.println("并发快排，数据量 " + arrLen + " 耗时（毫秒） " + stopwatch.elapsed(TimeUnit.MILLISECONDS));
             System.out.println("arr.length" + arr.length);
             for (int i = 1; i < arr.length; i++) {
                 if (arr[i - 1] > arr[i]) {
                     System.out.println(i);
                     System.out.println(arr[i - 1]);
                     System.out.println(arr[i]);
                     throw new RuntimeException("算法错误");
                 }
             }
             //System.out.println(Arrays.toString(arr));
         }
    }
    
    public void sort() {
        
        long processors = Runtime.getRuntime().availableProcessors();
        // 可以使用两倍于小核心的数量的线程来做
        //processors *= 2;
        
        System.out.println("CPU核心数 " + processors);
        
        long parallelBeginDeep = 0;
        long parThreadCount;
        while (true) {
            parThreadCount = 1 << parallelBeginDeep;
            if (parThreadCount >= processors) {
                System.out.println("最大并发线程数 " + parThreadCount);
                System.out.println("并发起始深度 parallelBeginDeep (start with 0) " + parallelBeginDeep);
                break;
            } else {
                ++parallelBeginDeep;
            }
        }
    
        ExecutorService exec = Executors.newFixedThreadPool((int) parThreadCount);
        
        CountDownLatch downLatch = new CountDownLatch((int) parThreadCount);

        //DoSort doSort = new DoSort(downLatch, parallelBeginDeep, exec, arr, 0, arr.length - 1);
        SortQuickSortParallelLongLong.QuickSortParallel quickSortParallel = new SortQuickSortParallelLongLong.QuickSortParallel(arr, 0, arr.length - 1, downLatch, parallelBeginDeep, exec);
        
        exec.execute(quickSortParallel);
        
        try {
            downLatch.await();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        
        exec.shutdown();
    }
    
    static class QuickSortParallel extends SortQuickSortParallelLongLong.QuickSort {
        
        private long deep;
        private ExecutorService exec;
        
        public QuickSortParallel(long[] arr, long left, long right, CountDownLatch downLatch, long deep, ExecutorService exec) {
            super(arr, left, right, downLatch);
            this.deep = deep;
            this.exec = exec;
        }
        
        @Override
        public void run() {
            long nil = doSort(left, right);
            
            if (deep > 1) {
                if (nil - 1 > left) {
                    exec.execute(new QuickSortParallel(arr, left, nil - 1, downLatch, deep - 1, exec));
                }
                if (nil + 1 < right) {
                    exec.execute(new QuickSortParallel(arr, nil + 1, right, downLatch, deep - 1, exec));
                }
            } else {
                if (nil - 1 > left) {
                    exec.execute(new QuickSort(arr, left, nil - 1, downLatch));
                }
                if (nil + 1 < right) {
                    exec.execute(new QuickSort(arr, nil + 1, right, downLatch));
                }
            }
            
        }
    }
    
    static class QuickSort implements Runnable {
        
        protected long[] arr;
        protected long left, right;
        protected CountDownLatch downLatch;
        
        public QuickSort(long[] arr, long left, long right, CountDownLatch downLatch) {
            this.arr = arr;
            this.left = left;
            this.right = right;
            this.downLatch = downLatch;
        }
        
        @Override
        public void run() {
            doSort_(left, right);
            if (downLatch != null) {
                downLatch.countDown();
//                System.out.println(getClass().getName() + "  " + hashCode()  + "  >>>>>>>>>>>>>>>>>>>>>>>>>>>> downLatch.countDown();");
            }


//            for (long i = left + 1; i < right; i++) {
//                if (arr[i - 1] > arr[i]) {
//                    throw new RuntimeException("error");
//                }
//            }
        }
        
        private long doSort_(long lef, long rig) {
            long nil = doSort(lef, rig);
            
            if (nil - 1 > lef) {
                doSort_(lef, nil - 1);
            }
            
            if (nil + 1 < rig) {
                doSort_(nil + 1, rig);
            }
            
            return nil;
        }
        
        protected long doSort(long lef, long rig) {
            
            long mv = arr[(int) lef];
            long nil = lef++;
            
            while (lef <= rig) {
                
                for (; rig > nil; rig--) {
                    if (arr[(int) rig] < mv) {
                        arr[(int) nil] = arr[(int) rig];
                        nil = rig--;
                        break;
                    }
                }
                
                for (; lef < nil; lef++) {
                    if (arr[(int) lef] > mv) {
                        arr[(int) nil] = arr[(int) lef];
                        nil = lef++;
                        break;
                    }
                }
            }
            
            arr[(int) nil] = mv;
            
            return nil;
            
        }
    }
}
