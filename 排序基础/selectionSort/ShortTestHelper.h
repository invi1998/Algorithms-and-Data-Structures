//
// 排序算法性能测试辅助函数
//

#ifndef SHORTTEDTHELPER_H
#define SHORTTEDTHELPER_H

#include <iostream>
#include <cassert>

using namespace std;

namespace SortTestHelper
{

  // 生成有n个元素的随机数组，每个元素的随机范围为[rangeL,rangeR]
  int *gennerateRandomArray(int n, int rangeL, int rangeR)
  {
    assert(rangeL <= rangeR);

    int *arr = new int[n];
    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
      arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
    }
    return arr;
  }

  // 生成一个近乎于有序的随机数组
  int *gennerateNearlyOrderArray(int n, int swapTimes)
  {
    // 先生成一个完全有序的数组
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
    {
      arr[i] = i;
    }

    // 随机挑选几对元素进行交换

    // 设置随机种子
    srand(time(NULL));

    for (int i = 0; i < swapTimes; i++)
    {
      int posx = rand() % n;
      int posy = rand() % n;
      swap(arr[posx], arr[posy]);
    }

    return arr;
  }

  template <typename T>
  void printArray(T arr[], int n)
  {
    for (int i = 0; i < n; i++)
    {
      std::cout << arr[i] << "  ";
    }
    std::cout << std::endl;

    return;
  }

  // void(*sort)(T[], int)
  // 函数指针，返回类型为void，参数类型T数组，int数组元素个数
  // sortName: 排序算法名（方便打印）
  // arr[] 要进行测试的测试用例
  // n 测试用例数组元素个数
  template <typename T>
  void testSort(string sortName, void (*sort)(T[], int), T arr[], int n)
  {
    clock_t startTime = clock();
    sort(arr, n);
    clock_t endTime = clock();

    // 检测sort算法是否正确
    assert(isSorted<T>(arr, n));

    std::cout << sortName << " : " << double(endTime - startTime) / CLOCKS_PER_SEC << " s " << std::endl;
    // 标准库中定义的一个宏
    // 表示每秒钟运行的时钟周期数

    return;
  }

  // 测试sort算法正确性
  template <typename T>
  bool isSorted(T arr[], int n)
  {
    for (int i = 0; i < n - 1; i++)
    {
      if (arr[i] > arr[i + 1])
      {
        return false;
      }
    }
    return true;
  }

  int *copyIntArray(int a[], int n)
  {
    int *arr = new int[n];

    // copy 第一个参数源数组的头指针，第二个参数源数组的尾指针, 第三个参数就是拷贝到目的地址的头指针
    copy(a, a + n, arr);

    return arr;
  }

}

#endif