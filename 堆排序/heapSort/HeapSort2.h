#ifndef HEAP_SORT_2_H
#define HEAP_SORT_2_H

#include <iostream>
#include "Heap.h"

using namespace std;

// 第二个基于堆的排序算法
template <typename T>
void heapSort2(T arr[], int n)
{
  // 首先在这个排序算法中，先实例化一个最大堆。存放的就是T类型的数据
  MaxHeap<T> maxheap = MaxHeap<T>(arr, n);
  // 这样，在这个构造函数里就完成了我们的 Heapify过程（数组建堆）

  // 接下来我们只需要不停地调用maxheap的extractMax就能将这些以从大到小的顺序取出来了
  // 但是如果我们希望排序结果是从小到大，为此，我们可以反向的来遍历一下这个n个数据，
  // 将maxheap中从extractMax返回的元素反向的返回到arr中就完成了从小到大的排序。
  for (int i = n - 1; i >= 0; i--)
  {
    arr[i] = maxheap.extractMax();
  }
}

#endif