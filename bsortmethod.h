#ifndef BSORTMETHOD_H
#define BSORTMETHOD_H

#include <QObject>

class BSortMethod : public QObject
{
    Q_OBJECT
public:
    explicit BSortMethod(QObject *parent = nullptr);

    void bubbleSort(int *vec, int len);                     // 冒泡排序

    void selectionSort(int *vec, int len);                  // 选择排序

    void insertionSort(int *vec, int len);                  // 插入排序

    void shellSort(int *vec, int len);                      // 希尔排序

    void merge(int *vec, int len);                          // 合并
    void mergeSort(int *vec, int len);                      // 归并排序

    void swap(int *vec, int i, int j);                      // 交换数据
    int partition(int *vec, int left, int right);           // 划分操作
    void quickSort(int *vec, int left, int right);          // 快速排序

    void heapify(int *vec, int i, int len);                 // 调整堆
    void heapSort(int *vec, int len);                       // 堆排序

    void countingSort(int *vec, int len);                   // 计数排序

    void bucketSort(int *vec, int len);                     // 桶排序
    void bucketSort2(int *vec, int len);                    // 桶排序

    void radixSort(int *vec, int len);                      // 基数排序
};

#endif // BSORTMETHOD_H
