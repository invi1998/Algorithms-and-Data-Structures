#ifndef HEAP_MAX_HEAP_H
#define HEAP_MAX_HEAP_H

#include <iostream>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cassert>

using namespace std;

// 最大堆类

template <typename Item>
class MaxHeap
{

private:
  Item *data;   // 存储堆中的数据的数组
  int count;    // 存储堆中有多少个元素
  int capacity; // 数组大小（堆中元素的容量上限）

  // 将K这个索引的位置的元素尝试着向上移动来维持堆的定义
  void shiftUp(int k)
  {
    // 我们每一次就是要看一下索引K这个位置，他的父节点（k/2）
    // 相应的元素是不是比k这个位置的元素还要小
    // 同时有索引存在，就需要考虑越界问题，这里我们就需要保证k是大于1的
    // 也就是k的取值最多到2，k到2的时候，就和k/2 = 1的那个父节点（也就是最顶部的节点）
    // 进行最后一次比较。这轮比较完成之后，k=1已经是这个树的跟节点了，已经不需要继续再进行比较了。
    while (k > 1 && data[k / 2] < data[k])
    {
      // 如果父节点的元素比k节点的元素还要小，说明此时违背了最大堆的定义。

      // 那么就把这个节点和其父节点进行位置交换
      swap(data[k], data[k / 2]);
      // 然后更新k的值
      k /= 2;
    }
  }

  void shiftDown(int k)
  {
    // 我们什么时候应该继续进行shiftDown操作呢？
    // 首先k这个索引所在的节点应该有孩子。怎么判断有孩子？在一个完全二叉树中，只要他有左孩子，那么我就能确定它有孩子
    // 这是因为在一个完全二叉树中它不可能只有右孩子没有左孩子
    while (2 * k <= count)
    {
      // 在这种情况下，我们要做的事情就是比较它的两个左右孩子，谁大和谁换。
      // 这个时候要注意，有可能这个节点没有右孩子。所以这里需要把这个边界情况考虑上

      // 为此我这里设置一个新的变量索引为j，j初始化成 2*k,这个j表示扫描意思呢？
      // 表示在此轮循环中，data[k]这哥元素应该喝data[j]这个位置元素交换
      // 因为它有左孩子，所以就有可能是和左孩子交换位置，这个就是初始化的值为 2*k
      int j = 2 * k;

      // 之后我们就判断一下它有没有右孩子，他的右孩子表示成 j+1 就可以了
      // 如果j+1<=count，说明它有右孩子，然后在右孩子存在的基础上比较两个左右孩子的大小
      if (j + 1 <= count && data[j + 1] > data[j])
      {
        // 如果右孩子比左孩子大，那么这里就把j更新成j+1.
        // 因为j是要进行交换的索引，注意这里谁大谁就是要交换的值
        j = j + 1;
      }
      // 继续判断，单前k节点是否比他要进行交换的子节点小，小就交换
      if (data[k] < data[j])
      {
        swap(data[k], data[j]);
        // 交换完成之后，我们k这个索引就变到了j这个位置
        k = j;
      }
      else
      {
        break;
      }
    }
  }

public:
  // 构造函数。这个构造函数最重要的功能就是为上面存储数据的数组开辟空间
  MaxHeap(int capacity)
  {
    data = new Item[capacity + 1];
    // 注意这里数组空间需要 + 1，是因为我们这个堆是从索引1开始标记，0号标记我们是不使用的

    count = 0;

    // 这里要注意，因为我们的这个数组值开辟了一次空间，也就是我们这个数组最多容纳 capacity
    // 这么多个元素，所以在我们的insert函数中也隐含着数组越界的问题
  }

  ~MaxHeap()
  {
    delete[] data;
  }

  // 查询堆中的元素个数
  int size()
  {
    return count;
  }

  // 查询是否是一个空堆
  bool isEmpty()
  {
    return count == 0;
  }

  // 往最大堆中添加一个新的元素
  void insert(Item item)
  {
    assert(count + 1 <= capacity);
    // 对于data来说，给他的[count+1]这个位置赋值为我们要插入的这个新元素item。
    // 在这里一定要注意，我们现在这个堆，对于我们的数组来说，索引是从1开始的，
    // 所以在这个堆中一共有count个元素存在，从1一直到count这些索引的位置中，
    // 和我们平时的数组 从0开始索引到count-1是有区别的，这里一定要小心
    data[count + 1] = item;
    // 我们的堆中多了一个元素，那么我们的计数器count就可以++
    count++;

    // 因为我们新加入的元素有可能破坏了堆的定义，所以这里调用我们提供的shiftUp方法来将这个元素向上移动来保持堆的定义
    shiftUp(count);
  }

  // 将堆中的最大值取出来。
  Item extractMax()
  {
    // 首先我们要从堆中取出一个最大值，第一步就是保证我们的堆不为空
    assert(count > 0);

    Item ret = data[1];

    // 将堆顶元素取出后，首先先将堆中最后一个元素放在堆顶位置
    swap(data[1], data[count]);
    // 交换完成之后，count--，表示最后这个元素（已经取出来的这个元素）我们再也不进行考虑了
    count--;

    // 然后要做的事情就是调用我们的shiftDown这个函数，想办法将这第一个元素向下挪，放在它合适的位置
    // 维持我们最大堆的性质。
    shiftDown(1);

    return ret;
  }

public:
  // 以树状打印整个堆结构(在控制台中以树的形式打印出堆的样子)
  // （使用限制就是只能打印100个元素以内的堆，同时这里也只支持打印int类型的堆）
  void testPrint()
  {

    // 我们的testPrint只能打印100个元素以内的堆的树状信息
    if (size() >= 100)
    {
      cout << "This print function can only work for less than 100 int";
      return;
    }

    // 我们的testPrint只能处理整数信息
    if (typeid(Item) != typeid(int))
    {
      cout << "This print function can only work for int item";
      return;
    }

    cout << "The max heap size is: " << size() << endl;
    cout << "Data in the max heap: ";
    for (int i = 1; i <= size(); i++)
    {
      // 我们的testPrint要求堆中的所有整数在[0, 100)的范围内
      assert(data[i] >= 0 && data[i] < 100);
      cout << data[i] << " ";
    }
    cout << endl;
    cout << endl;

    int n = size();
    int max_level = 0;
    int number_per_level = 1;
    while (n > 0)
    {
      max_level += 1;
      n -= number_per_level;
      number_per_level *= 2;
    }

    int max_level_number = int(pow(2, max_level - 1));
    int cur_tree_max_level_number = max_level_number;
    int index = 1;
    for (int level = 0; level < max_level; level++)
    {
      string line1 = string(max_level_number * 3 - 1, ' ');

      int cur_level_number = min(count - int(pow(2, level)) + 1, int(pow(2, level)));
      bool isLeft = true;
      for (int index_cur_level = 0; index_cur_level < cur_level_number; index++, index_cur_level++)
      {
        putNumberInLine(data[index], line1, index_cur_level, cur_tree_max_level_number * 3 - 1, isLeft);
        isLeft = !isLeft;
      }
      cout << line1 << endl;

      if (level == max_level - 1)
        break;

      string line2 = string(max_level_number * 3 - 1, ' ');
      for (int index_cur_level = 0; index_cur_level < cur_level_number; index_cur_level++)
        putBranchInLine(line2, index_cur_level, cur_tree_max_level_number * 3 - 1);
      cout << line2 << endl;

      cur_tree_max_level_number /= 2;
    }
  }

private:
  void putNumberInLine(int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft)
  {

    int sub_tree_width = (cur_tree_width - 1) / 2;
    int offset = index_cur_level * (cur_tree_width + 1) + sub_tree_width;
    assert(offset + 1 < line.size());
    if (num >= 10)
    {
      line[offset + 0] = '0' + num / 10;
      line[offset + 1] = '0' + num % 10;
    }
    else
    {
      if (isLeft)
        line[offset + 0] = '0' + num;
      else
        line[offset + 1] = '0' + num;
    }
  }

  void putBranchInLine(string &line, int index_cur_level, int cur_tree_width)
  {

    int sub_tree_width = (cur_tree_width - 1) / 2;
    int sub_sub_tree_width = (sub_tree_width - 1) / 2;
    int offset_left = index_cur_level * (cur_tree_width + 1) + sub_sub_tree_width;
    assert(offset_left + 1 < line.size());
    int offset_right = index_cur_level * (cur_tree_width + 1) + sub_tree_width + 1 + sub_sub_tree_width;
    assert(offset_right < line.size());

    line[offset_left + 1] = '/';
    line[offset_right + 0] = '\\';
  }
};

#endif