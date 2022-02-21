#include <iostream>
#include "HeapSort1.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "SortTestHelper.h"

using namespace std;

int main()
{
  int n = 1000000;
  std::cout << std::endl
            << "--------------------------------------------------------------------------------------" << std::endl;
  std::cout << "测试随机数组排序，数组大小为：" << n << "随机范围为 [0, " << n << "]" << std::endl;

  int *arr1 = SortTestHelper::gennerateRandomArray(n, 0, n);
  int *arr2 = SortTestHelper::copyIntArray(arr1, n);
  int *arr3 = SortTestHelper::copyIntArray(arr1, n);
  int *arr4 = SortTestHelper::copyIntArray(arr1, n);

  SortTestHelper::testSort("归并排序（Merge Sort）", megeSort, arr1, n);
  SortTestHelper::testSort("快速排序（Quick Sort）", quickSort2, arr2, n);
  SortTestHelper::testSort("三路快速排序（Quick Sort 3 ways）", quickSort3Ways, arr3, n);
  SortTestHelper::testSort("堆排序1（Heap Sort）", heapSort1, arr4, n);

  delete[] arr1;
  delete[] arr2;
  delete[] arr3;
  delete[] arr4;
  std::cout << "--------------------------------------------------------------------------------------" << std::endl
            << std::endl;

  std::cout << std::endl
            << "--------------------------------------------------------------------------------------" << std::endl;
  int m = 100;
  std::cout << "测试近乎有序的数组排序，数组大小为：" << n << "乱序数为：" << m << std::endl;

  arr1 = SortTestHelper::gennerateNearlyOrderArray(n, m);
  arr2 = SortTestHelper::copyIntArray(arr1, n);
  arr3 = SortTestHelper::copyIntArray(arr1, n);
  arr4 = SortTestHelper::copyIntArray(arr1, n);

  SortTestHelper::testSort("归并排序（Merge Sort）", megeSort, arr1, n);
  SortTestHelper::testSort("快速排序（Quick Sort）", quickSort2, arr2, n);
  SortTestHelper::testSort("三路快速排序（Quick Sort 3 ways）", quickSort3Ways, arr3, n);
  SortTestHelper::testSort("堆排序1（Heap Sort）", heapSort1, arr4, n);

  delete[] arr1;
  delete[] arr2;
  delete[] arr3;
  delete[] arr4;
  std::cout << "--------------------------------------------------------------------------------------" << std::endl
            << std::endl;

  std::cout << std::endl
            << "--------------------------------------------------------------------------------------" << std::endl;
  std::cout << "测试含有大量相同元素的数组排序，数组大小为：" << n << "随机范围为 [0, 10] " << std::endl;

  arr1 = SortTestHelper::gennerateRandomArray(n, 0, 10);
  arr2 = SortTestHelper::copyIntArray(arr1, n);
  arr3 = SortTestHelper::copyIntArray(arr1, n);
  arr4 = SortTestHelper::copyIntArray(arr1, n);

  SortTestHelper::testSort("归并排序（Merge Sort）", megeSort, arr1, n);
  SortTestHelper::testSort("快速排序（Quick Sort）", quickSort2, arr2, n);
  SortTestHelper::testSort("三路快速排序（Quick Sort 3 ways）", quickSort3Ways, arr3, n);
  SortTestHelper::testSort("堆排序1（Heap Sort）", heapSort1, arr4, n);

  delete[] arr1;
  delete[] arr2;
  delete[] arr3;
  delete[] arr4;
  std::cout << "--------------------------------------------------------------------------------------" << std::endl
            << std::endl;

  return 0;
}