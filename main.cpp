#include "bsortmethod.h"
#include "iostream"
using namespace std;

int main()
{
    int vec[15] = {3, 44, 38, 5, 47, 15, 36, 26, 27, 2, 46, 4, 19, 50, 48};
    int len = sizeof(vec) / sizeof(*vec);

    BSortMethod sortM;
//    sortM.bubbleSort(vec, len);       // 冒泡排序
//    sortM.selectionSort(vec, len);    // 选择排序
//    sortM.insertionSort(vec, len);    // 插入排序
//    sortM.shellSort(vec, len);        // 希尔排序
//    sortM.mergeSort(vec, len);        // 归并排序
//    sortM.quickSort(vec, 0, len-1);   // 快速排序
//    sortM.heapSort(vec, len);         // 堆排序
//    sortM.countingSort(vec, len);     // 计数排序
//    sortM.bucketSort(vec, len);       // 桶排序1
//    sortM.bucketSort2(vec, len);      // 桶排序2
    sortM.radixSort(vec, len);        // 基数排序

    for(int i = 0; i < 15; ++i)
        cout << vec[i] << " ";
    cout << endl;
}
