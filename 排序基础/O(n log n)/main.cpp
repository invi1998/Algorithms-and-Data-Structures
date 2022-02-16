
#include <iostream>
#include "ShortTestHelper.h"

using namespace std;

// 递归使用归并排序，对arr[l, ...r]的范围进行排序
template <typename T>
void __mergeSort(T arr[], int l, int r)
{
}

template <typename T>
void megeSort(T arr[], int n)
{
  // 在具体的实现中，归并排序的本质是一次递归的排序的过程，
  // 在这个过程中我们需要依次的对这个数组的不同部分继续进行一个归并排序
  // 为此我们这里会作为一个子函数。

  // 他的参数就是我们传递进来的这个数组以及单前要处理的数组的起始位置，以及结束位置
  __mergeSort(arr, 0, n - 1);

  // 注意，因为我们这个数组范围区间定义是一个前闭后闭的区间，也就是__mergeSort这个函数
  // 中，参数r的定义，这里我们定义为最后一个元素的位置，而不是最后一个元素后一个的位置。
  // 为此，我们这里掉用的就是n-1
  // 这个定义非常重要，在写算法的，这些细微的边界问题，很有可能会直接决定我们算法的准确信
}

int main()
{
  cout << "Hello World";

  return 0;
}
