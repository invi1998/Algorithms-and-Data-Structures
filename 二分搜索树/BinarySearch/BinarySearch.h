#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <iostream>
#include <cassert>

// 二分查找法，在有序数组中查找target
// 如果找到target，返回相对应的索引index
// 如果没有找到target，返回-1
// 普通的迭代版本的二分查找法
template <typename T>
int binarySearch(T arr[], int n, T target)
{
  // 首先申明两个变量,表示我需要在arr[l, r]这个前闭后闭区间内查找target
  int l = 0, r = n - 1;

  while (l <= r)
  {
    // int mid = (l+r)/2;
    // 注意这里，因为l和r都是int型，如果两个很大的int型相加，是很有可能超过int型的表达范围
    // int型溢出，这个程序就会产生bug
    // 怎么解决这个问题呢？那就不要使用加法，转而使用减法来求这个mid
    int mid = l + (r - l) / 2;

    if (arr[mid] == target)
    {
      return mid;
    }

    // 如果 中间值大于target，就在arr[l, mid-1]范围内继续查找
    if (arr[mid] > target)
    {
      r = mid - 1;
    }
    else // 如果 中间值小于target，就在arr[mid+1, r]范围内继续查找
    {
      l = mid + 1;
    }
  }

  return -1;
}

// --------------------------------------------------------------------------------------
template <typename T>
int __binarySearch2(T arr[], int l, int r, T target)
{
  if (l > r)
  {
    return -1;
  }

  int mid = l + (r - l) / 2;

  if (arr[mid] == target)
  {
    return mid;
  }
  else if (arr[mid] > target)
  {
    __binarySearch2(arr, l, mid - 1, target);
  }
  else
  {
    __binarySearch2(arr, mid + 1, r, target);
  }
}

// 递归版本的二分查找法
template <typename T>
int binarySearch2(T arr[], int n, T target)
{
  return __binarySearch2(arr, 0, n - 1, target);
}

#endif