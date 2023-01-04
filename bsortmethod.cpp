#include "bsortmethod.h"
#include "iostream"
using namespace std;

BSortMethod::BSortMethod(QObject *parent) : QObject(parent)
{

}

void BSortMethod::bubbleSort(int *vec, int len)
{
    // 每次遍历找到最大的数放在最右边，最后一个数不用比较，所以一共进行 len - 1 次遍历
    for ( int i = 1; i < len; ++i )
    {
        for ( int j = 0; j < len - i; ++j )
        {
            if ( vec[j] > vec[j+1] ) {
                int temp = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = temp;
            }
        }
    }
}

void BSortMethod::selectionSort(int *vec, int len)
{
    for ( int i = 0; i < len - 1; ++i )
    {
        int minIndex = i;

        // 每次遍历找到最小值的索引
        for ( int j = i + 1; j < len; ++j )
        {
            if ( vec[j] < vec[minIndex] ) {
                minIndex = j;
            }
        }

        // 把最小值放在有序序列的最后
        if ( minIndex != i ) {
            int temp = vec[minIndex];
            vec[minIndex] = vec[i];
            vec[i] = temp;
        }
    }
}

void BSortMethod::insertionSort(int *vec, int len)
{
    for ( int i = 0; i < len; ++i )
    {
        int preIndex = i - 1;
        int currentValue = vec[i];

        // 从后往前遍历有序列表，直到找到比当前数值小或者相等的数的索引，我们在这个索引后插入 currentValue
        while ( preIndex >= 0 && vec[preIndex] > currentValue )
        {
            vec[preIndex + 1] = vec[preIndex];
            preIndex--;
        }

        vec[preIndex+1] = currentValue;
    }
}

void BSortMethod::shellSort(int *vec, int len)
{
    // 初始增量 gap = len / 2，逐渐缩小增量 gap = gap / 2 直到变为 1
    for ( int gap = len / 2; gap >=1; gap = gap / 2 )
    {
        // 每一组进行排序
        for ( int i = gap; i < len; ++i )
        {
            int temp = vec[i];
            int j = i - gap;

            while ( j >= 0 && vec[j] > temp )
            {
                vec[j+gap] = vec[j];
                j -= gap;
            }

            vec[j+gap] = temp;
        }
    }
}

void BSortMethod::merge(int *vec, int len)
{
    int mid = len / 2;              // mid将数组从中间分割
    int *arr = new int[len];        // 临时数组（额外的内存空间）
    int s = 0;                      // 临时数组的起始位置
    int first = 0, second = mid;    // 两个数组的起始位置

    while ( first < mid && second < len )
    {
        // 比较大小
        if ( vec[first] <= vec[second] ) {
            arr[s++] = vec[first++];
        } else {
            arr[s++] = vec[second++];
        }
    }

    // 将剩余项复制到临时数组中
    while ( first < mid )
    {
        arr[s++] = vec[first++];
    }

    while ( second < len )
    {
        arr[s++] = vec[second++];
    }

    // 临时数组复制到原数组
    for (int i = 0; i < len; ++i)
    {
        vec[i] = arr[i];
    }

    // 内存释放
    delete []arr;
}

void BSortMethod::mergeSort(int *vec, int len)
{
    // 递归出口
    if ( len < 2 ) {
        return;
    }

    mergeSort(vec, len / 2);                    // 对前半部分进行归并排序
    mergeSort(vec + len / 2, len - len / 2);    // 对后半部分进行归并排序
    merge(vec, len);                            // 归并两部分
}

void BSortMethod::swap(int *vec, int i, int j)
{
    int temp = vec[i];
    vec[i] = vec[j];
    vec[j] = temp;
}

int BSortMethod::partition(int *vec, int left, int right)
{
    int pivot = left;
    int index = pivot + 1;
    int i = index;

    while ( i <= right )
    {
        if ( vec[i] < vec[pivot] ) {
            swap(vec, i, index);
            index += 1;
        }

        i += 1;
    }

    swap(vec, pivot, index - 1);

    // 返回最终划分完成后基准元素所在的位置
    return index - 1;
}

void BSortMethod::quickSort(int *vec, int left, int right)
{
    if ( left < right ) {
        int mid = partition(vec, left, right);
        quickSort(vec, left, mid - 1);
        quickSort(vec, mid + 1, right);
    }
}

void BSortMethod::heapify(int *vec, int i, int len)
{
    int left = i * 2 + 1;
    int right = i * 2 + 2;
    int largest = i;

    if ( left < len && vec[left] > vec[largest] ) {
        largest = left;
    }
    if ( right < len && vec[right] > vec[largest] ) {
        largest = right;
    }
    if ( largest != i ) {
        swap(vec, i, largest);
        heapify(vec, largest, len);
    }
}

void BSortMethod::heapSort(int *vec, int len)
{
    // 从最后一个非叶子节点开始向上遍历，创建堆
    for ( int i = len / 2 - 1; i >= 0; --i )
    {
        heapify(vec, i, len);
    }

    for ( int j = len - 1; j > 0; --j )
    {
        swap(vec, 0, j);
        heapify(vec, 0, j);
    }
}

void BSortMethod::countingSort(int *vec, int len)
{
    if ( len <= 0 ) {
        return;
    }

    // 找到数组最大值
    int max = vec[0];
    for ( int i = 1; i < len; ++i )
    {
        if ( vec[i] > max ) {
            max = vec[i];
        }
    }

    // 根据找到的最大值来确定统计数组的长度
    int arrayLen = max + 1;

    // 动态申请内存，并初始化为 0
    int *array = new int[arrayLen] {0};

    // 遍历数组，填充统计数组（把原数组中的数据变为统计数组的索引，值都是1）
    for ( int j = 0; j < len; ++j )
    {
        array[vec[j]]++;
    }

    int index = 0;
    for ( int k = 0; k < arrayLen; ++k )
    {
        // 遍历统计数组，再把排序后的索引变回数值存在原来数组中
        while ( array[k] > 0 )
        {
            vec[index++] = k;
            array[k]--;
        }
    }

    // 释放内存
    delete []array;
}

void BSortMethod::bucketSort(int *vec, int len)
{
    if ( len <= 0 ) {
        return;
    }

    // 找到数组最大值
    int max = vec[0];
    for ( int i = 1; i < len; ++i )
    {
        if ( vec[i] > max ) {
            max = vec[i];
        }
    }

    // 设置10个桶
    const int bucketNum = 10;

    // 定义二维数组
    std::vector<int> buckets[bucketNum];

    // 计算桶的最大尺寸
    int bucketSize = 1;
    while (max) {
        max /= 10;
        bucketSize *= 10;
    }
    bucketSize /= 10;

    // 数据存入桶中
    for ( int i = 0; i < len; ++i )
    {
        // 定义元素存放的桶号
        int index = vec[i] / bucketSize;
        buckets[index].push_back(vec[i]);

        // 对该桶使用插入排序
        for ( int j = int(buckets[index].size()) - 1; j > 0; --j )
        {
            if ( buckets[index][j] < buckets[index][j-1] ) {
                int temp = buckets[index][j];
                buckets[index][j] = buckets[index][j-1];
                buckets[index][j-1] = temp;
            }
        }
    }

    // 顺序访问桶，得到有序数组
    for ( int i = 0, k = 0; i < bucketNum; ++i )
    {
        for ( int j = 0; j < int(buckets[i].size()); ++j )
        {
            vec[k++] = buckets[i][j];
        }
    }
}

void BSortMethod::bucketSort2(int *vec, int len)
{
    if ( len <= 0 ) {
        return;
    }

    // 找到数组最大值，最小值
    int min = vec[0];
    int max = vec[0];
    for ( int i = 1; i < len; ++i)
    {
        if ( vec[i] < min ) min = vec[i];
        if ( vec[i] > max ) max = vec[i];
    }

    // 桶的大小
    int bucketNum = (max - min) / len + 1;

    // 二维数组动态分配内存
    int **buckets = new int* [bucketNum];
    for ( int i = 0; i < bucketNum; ++i )
    {
        buckets[i] = new int[bucketNum] {0};
    }

    // 动态分配内存，存储每个桶的元素个数
    int *array = new int[bucketNum] {0};

    // 数据存入桶中
    for ( int i = 0; i < len; ++i )
    {
        // 定义元素存放的桶号
        int index = (vec[i] - min) / len;

        // 参考计数排序，填充统计数组
        buckets[index][array[index]++] = vec[i];
    }

    int index = 0;
    for ( int i = 0; i < bucketNum; ++i )
    {
        // 使用快速排序
        quickSort(buckets[i], 0, array[i] - 1);
        cout << i << "号桶的元素个数：" << array[i] << endl;

        // 遍历桶中元素，依次存入原数组
        for ( int j = 0; j < array[i]; ++j )
        {
            vec[index++] = buckets[i][j];
        }
    }

    // 释放内存
    delete[] buckets;
    delete[] array;
}

void BSortMethod::radixSort(int *vec, int len)
{
    if ( len <= 0 ) {
        return;
    }

    // 找到数组最大值
    int max = vec[0];
    for ( int i = 1; i < len; ++i )
    {
        if ( vec[i] > max ) {
            max = vec[i];
        }
    }

    // 计算最大值的位数
    int maxBit = 1;
    while ( max > 10 * maxBit )
    {
        maxBit++;
    }

    for ( int k = 0; k < maxBit; ++k )
    {
        // 定义桶（二维数组）
        std::vector<std::vector<int>> bucket;
        for ( int i = 0; i < 10; ++i )
        {
            std::vector<int> temp;
            bucket.push_back(temp);
        }

        // 对每一位进行排序
        for ( int i = 0; i < len; ++i )
        {
            // 得到每位的基数
            int radix = int((vec[i] / (int)pow(10, k)) % 10);

            // 将对应的数组元素添加到相应位基数的桶中
            bucket[radix].push_back(vec[i]);
        }

        int index = 0;
        for ( int i = 0; i < 10; ++i )
        {
            // 计算桶的元素个数
            int size = (int)bucket[i].size();
            if ( size != 0 ) {
                // 桶不为空时，将桶中每个元素放回到数组中
                for ( int j = 0; j < size; ++j )
                {
                    vec[index++] = bucket[i][j];
                }
            }
        }
    }
}
