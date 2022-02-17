
#include <iostream>
#include "ShortTestHelper.h"
#include "InsertionSort.h"
#include "MergeSort.h"

using namespace std;

int main()
{
  int n = 50000;
  std::cout << "测试随机数组排序，数组大小 = " << n << ", 随机范围 [0, " << n << "]" << std::endl;

  int *arr1 = SortTestHelper::gennerateRandomArray(n, 0, n);
  int *arr2 = SortTestHelper::copyIntArray(arr1, n);
  int *arr5 = SortTestHelper::copyIntArray(arr1, n);

  SortTestHelper::testSort("插入排序（Insertion Sort） ", InsertionSort, arr1, n);
  SortTestHelper::testSort("归并排序（Merge Sort） ", megeSort, arr2, n);
  SortTestHelper::testSort("归并排序（Merge Sort BU）", mergeSortBU, arr5, n);

  // 测试随机数组排序，数组大小 = 50000, 随机范围 [0, 50000]
  // 插入排序（Insertion Sort）  : 2.28427 s
  // 归并排序（Merge Sort）  : 0.01264 s

  int swapTime = 10;

  std::cout << "测试近乎有序的数组排序，数组大小 = " << n << ", 乱序数: " << swapTime << std::endl;

  int *arr3 = SortTestHelper::gennerateNearlyOrderArray(n, swapTime);
  int *arr4 = SortTestHelper::copyIntArray(arr3, n);
  int *arr6 = SortTestHelper::copyIntArray(arr3, n);

  SortTestHelper::testSort("插入排序（Insertion Sort） ", InsertionSort, arr3, n);
  SortTestHelper::testSort("归并排序（Merge Sort） ", megeSort, arr4, n);
  SortTestHelper::testSort("归并排序（Merge Sort BU）", mergeSortBU, arr6, n);

  // 测试近乎有序��数组排序，数组大小 = 50000, 乱序数: 10
  // 插入排序（Insertion Sort）  : 0.001073 s
  // 归并排序（Merge Sort）  : 0.005798 s

  delete[] arr1;
  delete[] arr2;
  delete[] arr3;
  delete[] arr4;
  delete[] arr5;
  delete[] arr6;

  return 0;
}
