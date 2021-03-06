#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <iostream>
#include "InsertionSort.h"

using namespace std;

// 随机化快速排序

// 对arr[l, r]部分进行partition操作
// 注意这里返回值是int类型，返回的是索引值p，
// 这个p满足什么条件呢？运行完这个函数后，使得arr[p]前半部分全都小于arr[p]
// p索引后半部分全都大于arr[p];
// 使得arr[l, p-1] < arr[p] < arr[p+1, r]
template <typename T>
int __partition(T arr[], int l, int r)
{
  // 首先我们在快速排序中需要一个标准，我管这个标准叫做v
  // 这里这个比较标准我们这里就先简单的取要考察的这个数组的第一个元素
  // T v = arr[l];

  // 算法优化2
  // 上面我们每次标记点的元素都是选择数组中第一个元素，现在做优化，将这个标记点用一个随机选择的元素
  // 我们随机的这个元素要在l和r之间，首先就需要随机化一个数，rand() 然后除以这个范围（r-l+1），然后加上l这个偏移量
  // 这样一来我们就随机化生成一个[l,r]前闭后闭区间的一个索引范围的元素
  // arr[rand()%(r-l+1) +l];
  // 现在我需要将这个元素作为我们的标定元素v，其实很简单，将这个元素和我们最左边这个元素进行一下交换就好了
  swap(arr[l], arr[rand() % (r - l + 1) + l]);

  T v = arr[l]; // 然后继续走这行代码，取最左边这个元素，其实也就是我们上面交换过来设定的这个随机索引的元素

  // 接下来要做的就是逐步从l+1开始遍历整个数组
  // 让这整个数组从l+1之后分成两个部分
  // arr[l+1, j] < v < arr[j+1, i)
  // 这里为什么i是开区间呢？因为i这个位置就是我们单前正在考察的元素
  int j = l;
  for (int i = l + 1; i <= r; i++)
  {

    if (arr[i] < v)
    {
      // 当i位置当前考察的元素位置小于我们的标准比较值v
      // 那么就将arr[j+1]的元素和arr[i]位置的元素进行位置交换
      swap(arr[j + 1], arr[i]);
      // 交换完成 后j++，也就是我们将一个小于v的值交换到j这边的区间，让j区间扩充了一个元素
      j++;

      // 整个这个交换过程就是将第一个大于v的这个元素和单前正在考察的这个元素arr[i]进行了一次交换
      // 比如这里开始进来的时候，l=0,那么j = 0; i=1, j+1 = 1
      // 如果这个时候这个arr[i]小于v, 那么这里就要交换，这里交换arr[j+1]和arr[i]
      // 其实就将l后面的第一个元素arr[l+1]和arr[l+1]交换（自己交换自己）
      // 这是对于l=0的第一次交换，那么在这之后，j++了，i++了，在下一次的循环过程中，j就指向了那个交换过来的比v小的那个元素上，
      // 这其实也就是保证了j指向的元素永远都是比v小的 arr【l,j】 < V
      // 如果这个时候arr[i]还是小于v，那么一样的, arr[j+1]和arr[i]，继续自己交换自己，
      // 如果这个时候arr[i]大于了v，那么这个时候，j就不动，（因为j始终保证的j及其前面的都是小于v的）
      // 这个时候就不需要做交换，继续i++.，也就是arr[j+1, i)的元素都是遍历过，且大于v的，i是指向正在考察的元素，所以是开区间，
      // 这个元素还在进行比较，大小还不确定所以不能纳入任何一个区间
      // 那如果是这样的话，也就是j后面的元素（右边）扩从了一个元素（因为右边保存的是比V大的元素）
      // 然后继续遍历，这个时候，如果arr[i]小于这个V，那么就把j+1这个元素（j+1这个元素是大于V的，而arr[i]我们比较出来是小于v的)
      // 所以把小的放在左边，大的交换过来放在arr[i]的位置，同时j++,保证j始终指向左边小于v的最后一个元素

      //当然，上面的代码，如果熟悉了快速排序之后，可以改写成这个样子
      // swap(arr[++j], arr[i]);
      // 这个代码就是说，我们即交换了arr[j+1]，同时索引j又做了++更新
      // 这里为了清晰可见，就不采用这种写法了
    }
  }
  // 最后再遍历完之后，我们要做的事情就是将l这个位置的元素和j这个位置的元素进行一次交换
  // 这里为啥可以交换呢？
  // 因为上面我们分析了，j指向的那个元素永远都是小于v的那部分数组的最后一个元素位置，
  // 而我们的 V 取的位置就是数组的起始位置l，所以j这个小于V的元素可以放在左边，然后V和arr[j]
  // 交换，无非就是将数V这个中位数放在了它正确的位置，也就是交换之后，V前面的元素都是小于V的
  // v后面的元素都是大于v的
  swap(arr[l], arr[j]);

  // 此时我们的partion工作（找到v这个元素应该在的索引j）就完成了，直接返回j
  // j就是这里我们定义的这个索引p，它让整个数组左边arr[l, j]都是小于arr[j]，
  // 数组右边，arr[j+1, r]都是大于arr[j]
  return j;
}

// 对arr[l, r]部分进行快速排序
template <typename T>
void __quickSort(T arr[], int l, int r)
{
  // 因为是递归函数，所以首先对递归到底的情况进行处理（递归终止函数）
  // if(l>=r)
  // {
  //     return;
  // }
  // 算法优化1，在递归底层采用插入排序进行替代优化
  if (r - l <= 15)
  {
    insertionSort(arr, l, r);
    return;
  }

  // 下面开始快速排序
  // 首先我们需要调用一个叫做__partition的子函数对arr从l到r进行一个partition的操作
  // 这个partition的操作返回一个索引值
  int p = __partition(arr, l, r);
  // 当这个partition操作返回成功后,我们只需要很简单的继续递归调用__quickSort()
  // 对p左右两边继续递归调用__quickSort进行排序
  // 即arr[l, p-1]和arr[p+1, r]
  __quickSort(arr, l, p - 1);
  __quickSort(arr, p + 1, r);
}

// 快速排序算法
template <typename T>
void quickSort(T arr[], int n)
{
  // 算法优化2
  // 在开始排序之前，我们调用srand函数设置一下随机种子
  // 因为我们在此之后需要使用随机化的方式来设置我们的标定元素
  srand(time(NULL));

  // 快速排序也是需要使用递归的方式来进行排序
  __quickSort(arr, 0, n - 1);
}

// -----------------------------------------------------------------------------------------------------
// 双路快速排序

// 对arr[l, r]部分进行partition操作
// 返回p，使得arr[l, p-1] < arr[p] < arr[p+1, r]
template <typename T>
int __partition2(T arr[], int l, int r)
{
  // 一样的，在开始的时候，将这个[l, r]范围里的一个随机元素和数组的第一个元素进行一下交换
  swap(arr[l], arr[rand() % (r - l + 1) + l]);

  // 之后就可以放心的用我们新的这个开头元素作为标定点
  T v = arr[l];

  // 首先我们需要做两个临界点  i,j
  // arr[l+1, i） <= v， arr(j, r] >= v
  // i表示的是从l+1到i这个前闭后开的区间元素都是小于等于v的
  // j表示从 j 到 r 这个前开后闭的区间元素都是大于等于v的
  // 这个时候，就能想到，i的初始就是l+1，然后j的初始值就是r
  int i = l + 1, j = r;
  // 之后就可以开始我们的循环了
  while (true)
  {
    while (i <= r && arr[i] < v)
    {
      // 如果arr[i]比v还要小，那么我们就可以放心的i++
      // 继续让i往下遍历
      // 同样只要存在索引，就需要判断索引是否下标越界
      i++;
    }

    // 同样对于j来说也是一样的
    while (j >= l + 1 && arr[j] > v)
    {
      // 对于j来说，他的越界情况是j >= l+1，因为l最左边是保存着我们的标定点的，这个位置是被占了的
      // j是到达不了那个地方的
      j--;
    }

    // 这个时候，我们先来判断一下循环是否结束
    // 也就是说，通过这两次遍历之后，我们突然发现i比j还要大了，其实也就是说明我们整个循环已经遍历结束了
    if (i > j)
    {
      break;
    }
    // 否者的话，我们就能放心的交换这两个元素
    // 程序运行到这里，就说明i找到了左边 >= v的元素
    // j找到了右边 <= v 的元素
    // 这个时候只需要对i和j这连个位置的元素交换一下位置就可以
    swap(arr[i], arr[j]);
    // swap完之后我们 继续i往后走，j往前走
    i++;
    j--;
  }

  // 自此，我们就扫描完了整个数组arr，并且保证了在数组中arr[l+1, i） <= v， arr(j, r] >= v
  // 现在要做的就是将v这个元素放在我们整理完的这个数组它合适的位置
  // 首先，上面while循环结束，i这个索引所处的位置是 从前向后看是第一个大于等于v的元素的位置
  // 而j这个索引所处的位置，从后向前看，最后一个小于等于v的元素的位置
  // 注意上面这里的秒数，其实也就是说，遍历结束，i指向的位置已经指到大于等于v那部分区间去了
  // 而j这个索引所指向的位置已经指向小于等于v那部分区间去了
  // 很好理解，因为上面while循环跳出的条件就是 if(i>j)
  // 然后我们标定点v是在小于等于v这一段
  // 所以这里，j才是我们v这个元素应该存放的位置，将arr[l]和arr[j]进行一下位置交换
  swap(arr[l], arr[j]);

  // 此时我们j索引所指的位置就是partition所应该返回的 那个标定点应该所处的p的位置
  return j;
}

// 对arr[l, r]部分进行快速排序
template <typename T>
void __quickSort2(T arr[], int l, int r)
{
  if (r - l <= 15)
  {
    insertionSort(arr, l, r);
    return;
  }

  int p = __partition2(arr, l, r);
  __quickSort2(arr, l, p - 1);
  __quickSort2(arr, p + 1, r);
}

// 快速排序算法 2
template <typename T>
void quickSort2(T arr[], int n)
{
  srand(time(NULL));

  __quickSort2(arr, 0, n - 1);
}

// -----------------------------------------------------------------------------------------------------

// 三路快速排序 处理arr[l, r]

// 将arr[l, r]分为 < v;  == v; > v 的三部分
// 之后递归的对 < v; > v 这两个部分继续进行三路快速排序
template <typename T>
void __quickSort3Ways(T arr[], int l, int r)
{
  if (r - l <= 15)
  {
    insertionSort(arr, l, r);
    return;
  }

  // 下面我们开始正式的进行三路快速排序，
  // 由于我们的三路快速排序过程不是简单的返回一个索引p的位置，然后对p-1部分和p+1部分进行递归
  // 而对于中间等于v的部分是一个区间。为此我们partition的部分就不设计成一个函数了

  // partition 部分

  // 开始依旧和之前一样，随机选择一个元素和arr第一个元素arr[l]进行交换
  swap(arr[l], arr[rand() % (r - l + 1) + l]);

  // 将这个新的随机的元素设置为标定点v
  T v = arr[l];

  // 开始设置三路排序的索引
  int lt = l; // lt 初始值设置为l, 是为了保证arr[l+1, lt] 这个区间都是小于v, 初始lt = l,那么这个区间初始的时候就是空的

  int gt = r + 1; // gt的初始值设置为r+1, 是为了保证arr[gt, r]这个区间都是大于v的，初始值为r+1，那么这个区间初始的时候也就是空

  int i = l + 1; // i的初值设置为l+1，是为了保证arr[lt+1, i) 这个前闭后开的区间是 == v的。同时后开始以为对于i这个元素是我们正在考察的元素
  // 是不放在这个区间里的，与此同时可以看到，lt的初始值是l，那么lt+1的初始值也就是 l+1，i的初始值也是l+1，那么这个区间以为是前闭后开的，
  // 所以在初始的时候，这个 == v 的空间也是空的。

  // 这样就保证我们的这个算法逻辑有了一个正确的开始

  // 下面我们只需要写一个while循环，在while循环里，只要i和gt还没有碰头，也就是i < gt
  // 我们就可以进行相对应的分析操作
  while (i < gt)
  {
    // 我们整个过程有3中情况
    if (arr[i] < v)
    {
      swap(arr[i], arr[lt + 1]);
      lt++;
      i++;
    }
    else if (arr[i] > v)
    {
      swap(arr[i], arr[gt - 1]);
      gt--;
    }
    else // arr[i] == v
    {
      i++;
    }
  }

  // 经过这样一个过程，lt的指向是左边小于v这个区间的最后一个元素

  // 经过这样一个过程，我们只需要在最后swap一下arr[l] 和 arr[lt]
  // 将第一个元素（标定的元素v），相应的放到等于v这部分的前一个位置

  swap(arr[l], arr[lt]);

  // 注意这里，因为经过这样的排序之后，这里lt需要向前--一个位置才是它正确语义位置
  lt--; // 当然你也可以不再这里--，直接在下面的递归调用中进行lt-1也行

  // 然后我们继续对 [l, lt]和[gt, r]这连个小于 v 和大于v 的区间继续进行三路快速排序
  __quickSort3Ways(arr, l, lt);
  __quickSort3Ways(arr, gt, r);
}

template <typename T>
void quickSort3Ways(T arr[], int n)
{
  // 使用随机方式确定快速排序的标定点
  srand(time(NULL));
  __quickSort3Ways(arr, 0, n - 1);
}

// -----------------------------------------------------------------------------------------------------

// 利用快速排序思路查找数组中第n小的元素是谁

// 求出arr[l, r]范围里第k小的数
template <typename T>
T __selection(T arr[], int l, int r, int k)
{
  if (l == r)
  {
    return arr[l];
  }

  // partition之后，arr[p]的正确位置就在索引p上
  int p = __partition(arr, l, r);

  // 注意这里，这里我们使用的partition函数是随机化partition，而不是双路或者三路
  // 思考: 双路快排和三路快排的思想能不能用在selection算法中? :)

  if (k == p) // 如果k == p ，直接返回arr[p]
  {
    return arr[p];
  }
  else if (k < p) // 如果k<p,只需要在arr[l, p-1]中找地k小的元素即可
  {
    return __selection(arr, l, p - 1, k);
  }
  else
  {
    // 如果 k> p,则需要在arr[p_1, r]中去寻找第k-p-1小的元素
    // 注意：由于我们传入__selection的依然是arr, 而不是arr[p+1, r]
    // 所以传入的最后一个参数依然是k，而不是k-p-1
    return __selection(arr, p + 1, r, k);
  }
}

// 寻找arr数组中第k小的元素
// 注意：在我们的算法中，k是从0开始索引的，即最小的元素是第0小的元素，以此类推
// 如果希望我们的算法中k的语义是从1开始，只需要在整个逻辑开始进行k--即可，可以参考selection2
template <typename T>
T selection(T arr[], int n, int k)
{
  assert(k >= 0 && k < n);

  srand(time(NULL));

  return __selection(arr, 0, n - 1, k);
}

// 寻找arr数组中第 k 小的元素， k从1开始索引，即最小的元素是第1小元素，以此类推
template <typename T>
T selection2(T arr[], int n, int k)
{
  return selection(arr, n, k - 1);
}

#endif
