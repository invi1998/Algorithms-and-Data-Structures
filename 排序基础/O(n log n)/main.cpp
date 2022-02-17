
#include <iostream>
#include "ShortTestHelper.h"
#include "InsertionSort.h"

using namespace std;

// 将arr[l..mid]和arr[mid...r]这两部分进行归并
template <typename T>
void __merge(T arr[], int l, int mid, int r)
{
  // 对于这个归并。我们首先需要开辟一个临时的空间
  // 这个空间需要多大呢？
  // 需要r-l+1,是因为我们这里l和r都是闭空间，所以需要+1
  // 其实很好理解，比如l=0, r=3; [0, 3]是一个4个元素的数组大小，3-0+1 = 4
  T aux[r - l + 1];

  // 将我们要处理的这个arr数组中的元素全都复制到我们的辅助数组aux中
  for (int i = l; i <= r; i++)
  {
    // 在具体赋值的时候，要注意，我们的aux这个空间是从0开始的，
    // 但是我们的这arr这个空间是从l开始的，他们之间有一个l的偏移量
    // 所以我们赋值的时候应该是将arr的第i个元素赋值给aux的第i-l个元素
    aux[i - l] = arr[i];
  }

  // 设置两个索引指向这两个已经排好序的这两个子数组（左右两边）
  int i = l, j = mid + 1;

  // 使用一个新的索引k来进行遍历，来决定arr[k]的位置究竟应该是谁
  for (int k = l; k <= r; k++)
  {
    // i,j数组越界情况考虑
    // 我们能访问i-l和j-l的前提是i和j这两个索引还在这两个数组相应的位置里面（i还在左边数组里，j还在右边数组里）

    // 但是很有可能我们算法运行到一定的时候，对于i这个索引来说，它已经超出了它的范围，也就是i已经大于mid
    // 在这种情况如果我们的k还没有遍历完，就说明j索引所指的这数组中的元素（右边这个数组中的元素）
    // 还没有归并完全，这个时候我们的arr[k]就应该取的是aux[j-l]相应的位置的元素值
    if (i > mid)
    {
      // 其实说白了就是左边归并完了，右边还有值没归并，那么就直接将右边的值挨个放入arr[k]中
      arr[k] = aux[j - l];
      j++;
    }
    else if (j > r)
    {
      // 同样对于j越界，也是一样的，右边归并完了，但是左边还有值没有归并完，那就直接将左边挨个放入arr[k]中
      arr[k] = aux[i - l];
      i++;
    }
    // 如果这两个条件都不满足，才说明这个时候i和j都是有效的，这个时候才进行左右比对归并
    // 所以要先判断索引的合法性，才能放心的比较两个索引的值

    // 注意这里，也是同样的，因为有aux和arr之间有一个l的偏移，所以不能直接用aux[i]和aux[j]进行比较
    // 而是应该减去这个偏移
    else if (aux[i - l] < aux[j - l])
    {
      // 如果小于，那么显然arr[k]这个位置应该存放的就是aux[i-l]相应的这个元素
      arr[k] = aux[i - l];
      // 随后i往后走一个位置
      i++;
    }
    else
    {
      // 否者的话，arr[k]这个位置就应该存放aux[j-l]
      arr[k] = aux[j - l];
      // 同样j++
      j++;
    }
  }
}

// 递归使用归并排序，对arr[l, ...r]的范围进行排序
template <typename T>
void __mergeSort(T arr[], int l, int r)
{
  // 对于一个递归函数来说，我们首先要处理的就是递归到底的情况。
  // 很容易想到，当l<r的时候，我们要处理的这部分，就至少由两个元素，左边一个，右边一个
  // 这个时候我们还是需要进行一次排序
  // 但是当l>=r的时候，就表示我们只有一个元素，甚至一个元素都没有，l>r是不可能发生的情况
  // （也就是代表我们当前要处理的数据集为空）

  // 代码优化
  // if(l>=r)
  // {
  //     return;
  // }

  // 这里 r-1 = 15就表示有16个元素及其以下的时候使用插入排序
  if (r - l <= 15)
  {
    InsertionSort(arr, l, r);
    return;
  }

  // 否者的话我们就进行一次归并排序
  // 首先计算这个区间他的中点位置在哪？
  int mid = (l + r) / 2;
  // 注意这里有个隐含的潜在bug，就是当这个数据集非常大的时候（l和r都是非常大的int），这里l+r很可能会溢出int类型

  // 下面就可以对分开的左右两个部分分别进行归并排序
  __mergeSort(arr, l, mid);
  __mergeSort(arr, mid + 1, r);

  // 这两部分都归并排序好之后，就要使用merge将归并排序好的这两个部分
  // 从l-mid,在从mid-r这两部分进行一个merge操作

  // 代码优化：
  // 在我们对数组的左右两边进行递归的归并排序之后，不管三七二十一，
  // 直接下一句操作就是将这左右两边的数组进行merge合并操作。
  // 但是这个时候其实如果左边的最大值小于等于右边的最小值（也就是 arr[mid] <= arr[mid+1]），
  // 那么就说明这个arr数组已经是有序的了。就不再需要进行merge操作了。

  if (arr[mid] > arr[mid + 1])
  {
    __merge(arr, l, mid, r);
  }

  // 这次merge完成之后我们就完成了整个归并排序的过程
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
  int n = 50000;
  std::cout << "测试随机数组排序，数组大小 = " << n << ", 随机范围 [0, " << n << "]" << std::endl;

  int *arr1 = SortTestHelper::gennerateRandomArray(n, 0, n);
  int *arr2 = SortTestHelper::copyIntArray(arr1, n);

  SortTestHelper::testSort("插入排序（Insertion Sort） ", InsertionSort, arr1, n);
  SortTestHelper::testSort("归并排序（Merge Sort） ", megeSort, arr2, n);

  // 测试随机数组排序，数组大小 = 50000, 随机范围 [0, 50000]
  // 插入排序（Insertion Sort）  : 2.28427 s
  // 归并排序（Merge Sort）  : 0.01264 s

  int swapTime = 10;

  std::cout << "测试近乎有序的数组排序，数组大小 = " << n << ", 乱序数: " << swapTime << std::endl;

  int *arr3 = SortTestHelper::gennerateNearlyOrderArray(n, swapTime);
  int *arr4 = SortTestHelper::copyIntArray(arr3, n);

  SortTestHelper::testSort("插入排序（Insertion Sort） ", InsertionSort, arr3, n);
  SortTestHelper::testSort("归并排序（Merge Sort） ", megeSort, arr4, n);
  // 测试近乎有序��数组排序，数组大小 = 50000, 乱序数: 10
  // 插入排序（Insertion Sort）  : 0.001073 s
  // 归并排序（Merge Sort）  : 0.005798 s

  delete[] arr1;
  delete[] arr2;
  delete[] arr3;
  delete[] arr4;

  return 0;
}
