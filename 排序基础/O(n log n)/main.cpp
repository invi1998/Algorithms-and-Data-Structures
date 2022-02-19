
#include <iostream>
#include "SortTestHelper.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"

using namespace std;

int main()
{
  int n = 50000;
  std::cout << "测试随机数组排序，数组大小 = " << n << ", 随机范围 [0, " << n << "]" << std::endl;

  int *arr1 = SortTestHelper::gennerateRandomArray(n, 0, n);
  int *arr2 = SortTestHelper::copyIntArray(arr1, n);
  int *arr5 = SortTestHelper::copyIntArray(arr1, n);

  SortTestHelper::testSort("插入排序（Insertion Sort） ", insertionSort, arr1, n);
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

  SortTestHelper::testSort("插入排序（Insertion Sort） ", insertionSort, arr3, n);
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

  // -------------------------------------------------------------------------
  std::cout << std::endl;

  int m = 1000000;
  std::cout << "-------------------------------------------------------------------------" << std::endl;
  int *arrbw1 = SortTestHelper::gennerateRandomArray(m, 0, m);
  int *arrbw2 = SortTestHelper::copyIntArray(arrbw1, m);
  int *arrbw7 = SortTestHelper::copyIntArray(arrbw1, m);
  int *arrbw10 = SortTestHelper::copyIntArray(arrbw1, m);

  SortTestHelper::testSort("归并排序（Merge Sort）", megeSort, arrbw1, m);
  SortTestHelper::testSort("随机化快速排序（Quick Sort）", quickSort, arrbw2, m);
  SortTestHelper::testSort("双路快速排序（Quick Sort）", quickSort2, arrbw7, m);
  SortTestHelper::testSort("三路快速排序（Quick Sort）", quickSort3Ways, arrbw10, m);

  std::cout << "-------------------------------------------------------------------------" << std::endl;
  std::cout << std::endl;
  std::cout << "-------------------------------------------------------------------------" << std::endl;
  int swapTime2 = 100;
  std::cout << "测试近乎有序的数组排序：数组大小 " << m << ", 乱序数：" << swapTime2 << std::endl;
  int *arrbw3 = SortTestHelper::gennerateNearlyOrderArray(m, swapTime2);
  int *arrbw4 = SortTestHelper::copyIntArray(arrbw3, m);
  int *arrbw8 = SortTestHelper::copyIntArray(arrbw3, m);
  int *arrbw11 = SortTestHelper::copyIntArray(arrbw3, m);

  SortTestHelper::testSort("归并排序（Merge Sort）", megeSort, arrbw3, m);
  SortTestHelper::testSort("快速排序（Quick Sort）", quickSort, arrbw4, m);
  SortTestHelper::testSort("双路快速排序（Quick Sort）", quickSort2, arrbw8, m);
  SortTestHelper::testSort("三路快速排序（Quick Sort）", quickSort3Ways, arrbw11, m);

  std::cout << "-------------------------------------------------------------------------" << std::endl;

  std::cout << std::endl;
  std::cout << "-------------------------------------------------------------------------" << std::endl;

  std::cout << "测试有大量重复数据的数组排序：数组大小 " << m << std::endl;
  int *arrbw5 = SortTestHelper::gennerateRandomArray(m, 0, 10);
  int *arrbw6 = SortTestHelper::copyIntArray(arrbw5, m);
  int *arrbw9 = SortTestHelper::copyIntArray(arrbw5, m);
  int *arrbw12 = SortTestHelper::copyIntArray(arrbw5, m);

  SortTestHelper::testSort("归并排序（Merge Sort）", megeSort, arrbw5, m);
  SortTestHelper::testSort("快速排序（Quick Sort）", quickSort, arrbw6, m);
  SortTestHelper::testSort("双路快速排序（Quick Sort）", quickSort2, arrbw9, m);
  SortTestHelper::testSort("三路快速排序（Quick Sort）", quickSort3Ways, arrbw12, m);

  std::cout << "-------------------------------------------------------------------------" << std::endl;

  // m = 3;

  int *arrbw13 = SortTestHelper::gennerateRandomArray(m, 0, m); // 完全随机
  int *arrbw14 = SortTestHelper::generateOrderedArray(m);       // 完全有序
  int *arrbw15 = SortTestHelper::generateInversedArray(m);      // 完全逆序

  std::cout << std::endl;

  std::cout << m << "大小的完全随机的数组【逆序对】: \t" << inversionCount(arrbw13, m) << std::endl;
  std::cout << m << "大小的完全有序的数组【逆序对】: \t" << inversionCount(arrbw14, m) << std::endl;
  std::cout << m << "大小的完全逆序的数组【逆序对】: \t" << inversionCount(arrbw15, m) << std::endl;

  delete[] arrbw1;
  delete[] arrbw2;
  delete[] arrbw3;
  delete[] arrbw4;
  delete[] arrbw5;
  delete[] arrbw6;
  delete[] arrbw7;
  delete[] arrbw8;
  delete[] arrbw9;
  delete[] arrbw10;
  delete[] arrbw11;
  delete[] arrbw12;
  delete[] arrbw13;
  delete[] arrbw14;
  delete[] arrbw15;

  return 0;
}
