#ifndef HEAP_MAX_HEAP_H
#define HEAP_MAX_HEAP_H

#include <iostream>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cassert>

using namespace std;

// 最大堆类

template <typename Item>
class MaxHeap
{

private:
  Item *data; // 存储堆中的数据的数组
  int count;  // 存储堆中有多少个元素

public:
  // 构造函数。这个构造函数最重要的功能就是为上面存储数据的数组开辟空间
  MaxHeap(int capacity)
  {
    data = new Item[capacity + 1];
    // 注意这里数组空间需要 + 1，是因为我们这个堆是从索引1开始标记，0号标记我们是不使用的

    count = 0;
  }

  ~MaxHeap()
  {
    delete[] data;
  }

  // 查询堆中的元素个数
  int size()
  {
    return count;
  }

  // 查询是否是一个空堆
  bool isEmpty()
  {
    return count == 0;
  }
};

#endif