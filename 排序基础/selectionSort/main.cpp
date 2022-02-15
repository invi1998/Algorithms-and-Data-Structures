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

// 插入排序

template <typename T>
void insertionSort(T arr[], int n)
{
  // 注意这里，插入排序第一层遍历从1开始，为什么？
  // 因为对于插入排序来说，第0个元素我们根本可以不用考虑
  // 因为对于插入排序来说，第0个元素放在那里，它本身就已经有序了
  // 我们不再需要把它插入到前面的任何一个位置(第0个元素前面也没有位置)
  // 所以我们开始遍历的时候是直接从第二个元素(索引值为1这个元素开始考察的)
  for (int i = 1; i < n; i++)
  {
    // 然后在这个循环里我们做的事情是什么？
    // 寻找元素arr[i]合适的插入位置
    // 这个合适的插入位置是在前面
    // 所以这里这层循环我们是从这个位置向前倒。知道j>0为止
    // 注意这里是j>0而不是j>=0,为什么？
    // 因为我们这层循环是和当前元素的前一个位置元素进行比较，看看能不能放在前一个元素的位置
    // 可以想象，这个比较最后发生的位置，应该是j = 1的时候，这个时候就是位置1的元素和位置0的元素做比较
    // 看位置1能不能插入到位置0，如果能，就交换位置
    // 所以我们最多考察到j=1这个位置（也就是j>0）

    // for(int j = i; j > 0; j--)
    // {
    //     if(arr[j] < arr[j-1])
    //     {
    //         swap(arr[j], arr[j-1]);
    //     }
    //     // 如果在这里我们已经发现j这个位置的元素已经大于等于它前面位置的元素，
    //     // 那么就没有必要继续遍历比较下去了，j这个位置已经是合适的位置了
    //     // 这个时候直接终止这次循环就可以了
    //     else
    //     {
    //         break;
    //     }
    // }

    // 所以这里也可以看到插入排序理论上比选择排序效率高的一个表现就是插入排序它是有提前结束遍历的条件的
    // 而选择排序则没有，需要完整跑完全部数据

    // 其实这里也可以直接这样写
    for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
    {
      swap(arr[j], arr[j - 1]);
    }
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
  // int n = 10000;
  int *arrTest1 = SortTestHelper::gennerateRandomArray(n, 0, n);
  int *arrTest2 = SortTestHelper::copyIntArray(arrTest1, n);
  SortTestHelper::testSort("选择排序（Selection sort）", SelectionSort, arrTest1, n);
  SortTestHelper::testSort("插入排序（Selection sort）", insertionSort, arrTest2, n);

  // 选择排序（Selection sort） : 14.6116 s
  // 插入排序（Selection sort） : 30.4101 s

  delete[] arrTest1;
  delete[] arrTest2;

  std::cout << "----------------------------------------------------------------------" << std::endl;

  return 0;
}