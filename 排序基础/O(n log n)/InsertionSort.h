#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <iostream>

using namespace std;

// 插入排序

template <typename T>
void InsertionSort(T arr[], int n)
{
  for (int i = 1; i < n; i++)
  {
    T e = arr[i];

    int j;
    for (j = i; j > 0 && arr[j - 1] > e; j--)
    {
      arr[j] = arr[j - 1];
    }
    arr[j] = e;
  }
}

#endif