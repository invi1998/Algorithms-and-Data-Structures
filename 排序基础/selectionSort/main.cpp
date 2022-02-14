#include <iostream>
// #include <algorithm>     c++11之前使用swap函数需要引入这个头文件，c++11之后，swap被包含在了标准库std中
#include "Student.h"

#include "ShortTestHelper.h"

using namespace std;

// 选择排序

// arr 一个int型的数组（这里暂时先定为int型，后续改造为模板函数）
// n 数组大小（数组中元素个数）
template <typename T>
void SelectionSort(T arr[], int n)
{
  for (int i = 0; i < n; i++)
  {
    // 在这个for循环中，我们要做的事情就是寻找当前
    // [ i, n ) 这个前闭后开区间内最小的元素

    // 那这里就先设置一个新的int型
    // 用于保存数组中最小值所在的索引值
    // 初始化为 i 的位置
    int minIndex = i;

    // 之后我们就能再进行一次循环
    for (int j = i + 1; j < n; j++)
    {
      // 在这层循环中，每次我们来比较我们所看到的j位置的元素。是否小于最小值minindex所在的元素值
      if (arr[j] < arr[minIndex])
      {
        // 如果小于，我们就需要更新一下当前这个minIndex，让他等于j
        minIndex = j;
      }
    }

    // 至此，在一轮循环中，我们就找到了i-n中最小的元素的索引 minIndex
    // 那这个时候，只需要将 i 位置的元素和我们找到的最小的minIndex位置的元素进行交换
    // 就完成了一轮排序
    swap(arr[i], arr[minIndex]);
    // 这样进行n轮排序，就能将数组中所有的元素从小到大排序完成
  }
}

int main()
{
  int arr[] = {10, 23, 5, 2, 22, 9, 6, 11, 45};

  SelectionSort(arr, sizeof(arr) / sizeof(int));

  for (int i = 0, n = sizeof(arr) / sizeof(int); i < n; i++)
  {
    std::cout << arr[i] << "  ";
  }
  // 2  5  6  9  10  11  22  23  45

  std::cout << std::endl;

  float arr2[] = {10.23f, 2.3f, 0.5f, 2.22f, 22.77f, 19.01f, 1.6f, 1.1f, 4.5f};

  SelectionSort(arr2, sizeof(arr2) / sizeof(float));

  for (int i = 0, n = sizeof(arr2) / sizeof(float); i < n; i++)
  {
    std::cout << arr2[i] << "  ";
  }
  // 0.5  1.1  1.6  2.22  2.3  4.5  10.23  19.01  22.77

  std::cout << std::endl;

  string arr3[] = {"D", "a", "F", "c", "S", "b"};

  SelectionSort(arr3, sizeof(arr3) / sizeof(string));

  for (int i = 0, n = sizeof(arr3) / sizeof(string); i < n; i++)
  {
    std::cout << arr3[i] << "  ";
  }
  // D  F  S  a  b  c

  std::cout << std::endl;

  Student arr4[] = {
      {"A",
       90},
      {"C",
       70},
      {"D",
       10},
      {"E",
       67},
      {"a",
       10},
      {"H",
       67}};

  SelectionSort(arr4, sizeof(arr4) / sizeof(Student));

  for (int i = 0, n = sizeof(arr4) / sizeof(Student); i < n; i++)
  {
    std::cout << arr4[i];
  }
  // Student: A  90
  // Student: C  70
  // Student: E  67
  // Student: H  67
  // Student: D  10
  // Student: a  10

  std::cout << std::endl;

  std::cout << "----------------------------------------------------------------------" << std::endl;

  int n = 100000;
  int *arrTest = SortTestHelper::gennerateRandomArray(n, 0, n);
  SortTestHelper::testSort("选择排序（Selection sort）", SelectionSort, arrTest, n);

  // 选择排序（Selection sort） : 16.9211 s

  delete[] arrTest;

  return 0;
}