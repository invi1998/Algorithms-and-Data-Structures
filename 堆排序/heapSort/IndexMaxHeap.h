#ifndef INDEX_MAX_HEAP_H
#define INDEX_MAX_HEAP_H

#include <iostream>
#include <cassert>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;

// 索引最大堆

template <typename Item>
class IndexMaxHeap
{

private:
  Item *data;
  int *indexes; // 存储索引堆中的索引
  int *reverse; // reverse[i]就表示索引 i 在indexes堆中相应的位置
  int count;
  int capacity;

  // 将K这个索引的位置的元素尝试着向上移动来维持堆的定义
  void shiftUp(int k)
  {
    // 我们每一次就是要看一下索引K这个位置，他的父节点（k/2）
    // 相应的元素是不是比k这个位置的元素还要小
    // 同时有索引存在，就需要考虑越界问题，这里我们就需要保证k是大于1的
    // 也就是k的取值最多到2，k到2的时候，就和k/2 = 1的那个父节点（也就是最顶部的节点）
    // 进行最后一次比较。这轮比较完成之后，k=1已经是这个树的跟节点了，已经不需要继续再进行比较了。

    // 这里要注意，首先我们比较的依旧是data里的数据，但是这个时候因为是索引堆，堆数组中存放的是data数据对应的索引
    // 所以这个时候我们就需要通过k这个堆节点索引去index里找到那个真正的data元素的索引（这里有点绕，需要好好理解）
    // 所以这里就是为什么我们要拿到data数据需要套一层indexes这个数组
    while (k > 1 && data[indexes[k / 2]] < data[indexes[k]])
    {
      // 如果父节点的元素比k节点的元素还要小，说明此时违背了最大堆的定义。

      // 那么就把这个节点和其父节点进行位置交换
      // 注意这里进行交换的时候，不是交换data数组里的数据，（因为本身索引堆就是为了避免直接操作data数据）
      // 这里交换的是交换data的索引数据（本身我们索引堆维护的也是这个索引数组）
      swap(indexes[k], indexes[k / 2]);
      // 将indexes中这两个位置进行了交换，相应的也需要维护reverse
      // 换句话说，由于这里这个交换操作，使得k/2和k这两个索引的位置发生了改变，
      // 那么这里就要维护相对应的k/2和k的reverse
      reverse[indexes[k / 2]] = k / 2;
      reverse[indexes[k]] = k;
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
      //   同样的，我们对data的任何操作都不能直接通过之前的一层索引直接指向data元素
      // 都需要通过indexes的间接索引去获取这个元素的索引，然后才能根据这个索引去拿到data元素
      if (j + 1 <= count && data[indexes[j + 1]] > data[indexes[j]])
      {
        // 如果右孩子比左孩子大，那么这里就把j更新成j+1.
        // 因为j是要进行交换的索引，注意这里谁大谁就是要交换的值
        j = j + 1;
      }
      // 继续判断，单前k节点是否比他要进行交换的子节点小，小就交换
      if (data[indexes[k]] < data[indexes[j]])
      {
        // 因为索引堆维护的是索引数组，所以这里交换的就是索引的值
        swap(indexes[k], indexes[j]);
        // 交换完成之后，我们k这个索引就变到了j这个位置

        // 修改了indexes这个数组，所以相对应的就需要维护k和j的reverse
        reverse[indexes[k]] = k;
        reverse[indexes[j]] = j;

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
  IndexMaxHeap(int capacity)
  {
    data = new Item[capacity + 1];
    // 注意这里数组空间需要 + 1，是因为我们这个堆是从索引1开始标记，0号标记我们是不使用的

    indexes = new int[capacity + 1];

    reverse = new int[capacity + 1];

    // 这里要注意
    // reverse[i]表示的是i这个索引在在堆中的位置，我们应该取一个标记值，
    // 用于表明如果i这个索引不存在，那么reverse[i]应该是什么
    // 在这里我们初始化，将这个reverse全都初始化为0，也就是说在我们这个堆里，
    // 一个元素都没有，所以i这个索引所对应的位置全都指向0，
    // 这里因为我们的堆是从1开始索引的，所以这里指向0实际上是没有意义的
    // reverse[i] = 0就表示i这个索引在堆中根本就不存在
    for (int i = 0; i <= capacity; i++)
    {
      reverse[i] = 0;
    }

    count = 0;

    // 这里要注意，因为我们的这个数组值开辟了一次空间，也就是我们这个数组最多容纳 capacity
    // 这么多个元素，所以在我们的insert函数中也隐含着数组越界的问题
    this->capacity = capacity;
  }

  // 构造函数，该构造函数我们传入一个数组参数arr和数组元素个数n
  IndexMaxHeap(Item *arr, int n)
  {
    // 这个构造函数，首先依旧是需要对data这个数组指针开空间
    data = new Item[n + 1];
    capacity = n;
    for (int i = 0; i < n; i++)
    {
      // 注意这里，因为我们data是从1开始的，所以在赋值的时候需要i+1，跳过第0个元素
      data[i + 1] = arr[i];
    }
    // 数据遍历赋值完毕之后，我们的堆数组中就有n个元素了
    count = n;

    // 之后就开始我们的 Heapify过程了
    // 从count/2开始（也就是完全二叉树的第一个非叶子节点索引，以后没次从该索引-1都是非叶子节点）
    for (int i = count / 2; i >= 1; i--)
    {
      // 然后每次对这个i索引的节点进行shiftDown操作
      shiftDown(i);
    }

    // 执行完上面这次循环之后，我们的data这个数组就被建成了一个最大堆
  }

  ~MaxHeap()
  {
    delete[] data;
    delete[] indexes;
    delete[] reverse;
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

  // 往索引最大堆中添加一个新的元素
  // 这里因为是一个索引堆，所以在往一个索引堆中插入元素的时候，还需要同时指定该元素的索引
  // 同时这里需要注意，因为这里我们的索引堆依旧是从1开始的，但是索引对于外部用户来说，依旧是正常的从0开始的
  // 所以我们需要在索引堆的内部来处理这个差异
  void insert(int i, Item item)
  {

    assert(count + 1 <= capacity);
    assert(i + 1 >= 1 && i + 1 <= capacity);

    // 检测完索引越界后，将i+1，让他从0开始的索引变成从1开始
    i += 1;

    // 然后我们就可以插入这个元素了
    // 对于索引堆来说，这里的data就是存的索引i对应的那个用户指定的元素值
    data[i] = item;
    // 然后相应的 indexes[count+1]的位置添加上传入的这个新的索引i
    indexes[count + 1] = i;
    reverse[i] = count + 1;
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

    // 注意此时堆顶的元素不是data[1]，而是data[indexes[1]]
    Item ret = data[indexes[1]];

    // 将堆顶元素取出后，首先先将堆中最后一个元素放在堆顶位置
    // 注意，同样的，交换的时候也是交换的indexes这个索引数组中的元素
    swap(indexes[1], indexes[count]);
    // 交换完成之后，count--，表示最后这个元素（已经取出来的这个元素）我们再也不进行考虑了

    // 上面这句交换操作修改了indexes中的索引位置，那么就需要维护相对应的reverse数组
    reverse[indexes[1]] = 1;

    reverse[indexes[count]] = 0;
    // 而对于reverse[indexes[count]]它的值我们这里需要注意，他的值在上面这步交换中
    // 相当于把栈顶的元素放到了最后，之后我们要通过count--将这个元素移除出堆
    // 通过之前对于reverse的定义，我们知道，删除一个元素，就表示这个元素不存在
    // 指向一个不存在的元素，就让它指向0就可以

    count--;

    // 然后要做的事情就是调用我们的shiftDown这个函数，想办法将这第一个元素向下挪，放在它合适的位置
    // 维持我们最大堆的性质。
    shiftDown(1);

    return ret;
  }

  // 返回堆中最大元素的索引（因为获得了这个索引，就可以直接在data中找到这个元素）
  int extractMaxIndex()
  {
    // 首先我们要从堆中取出一个最大值，第一步就是保证我们的堆不为空
    assert(count > 0);

    // 注意此时堆顶的元素不是data[1]，而是data[indexes[1]]
    // 对应的，如果只是需要最大元素的索引值，那就是 indexes[1]
    // 因为我们希望用户使用的索引是正常的从0开始的索引，所以这里需要将得到的索引值-1
    // 将我们类里从1开始的索引转为从0开始的索引
    int ret = indexes[1] - 1;

    // 将堆顶元素取出后，首先先将堆中最后一个元素放在堆顶位置
    // 注意，同样的，交换的时候也是交换的indexes这个索引数组中的元素
    swap(indexes[1], indexes[count]);
    // 交换完成之后，count--，表示最后这个元素（已经取出来的这个元素）我们再也不进行考虑了

    // 上面这句交换操作修改了indexes中的索引位置，那么就需要维护相对应的reverse数组
    reverse[indexes[1]] = 1;

    reverse[indexes[count]] = 0;
    // 而对于reverse[indexes[count]]它的值我们这里需要注意，他的值在上面这步交换中
    // 相当于把栈顶的元素放到了最后，之后我们要通过count--将这个元素移除出堆
    // 通过之前对于reverse的定义，我们知道，删除一个元素，就表示这个元素不存在
    // 指向一个不存在的元素，就让它指向0就可以

    count--;

    // 然后要做的事情就是调用我们的shiftDown这个函数，想办法将这第一个元素向下挪，放在它合适的位置
    // 维持我们最大堆的性质。
    shiftDown(1);

    return ret;
  }

  //   用于判断我们当前这个索引堆真的包含i这个索引
  bool contain(int i)
  {
    assert(i >= 1 && i <= capacity);
    //   他的判断逻辑很简单，只需要判断reverse[i+1]是否等于0,等于0表示i+1这个索引没有堆元素
    return reverse[i] != 0;
  }

  //   同样，因为我们这个是一个最大索引堆，所以用户就还能得到一个很方便的操作
  // 通过给定一个索引值i，去找到对应的数组元素
  Item getItem(int i)
  {
    assert(contain(i + 1));
    // 同样，对于用户来说它使用的索引是从0开始的，但是我们类里的是从1开始的
    // 所以这里要+1
    return data[i];
  }

  // 最后一个操作
  // 外部用户希望将索引为i的这个内容，修改成一个新的item
  // 注意这个时候，不仅仅是修改data值这么简单那，还需要维护我们的最大索引堆的定义
  void change(int i, Item newItem)
  {
    //   这里程序代码依旧存在潜在的风险，风险在于对于用户传入的这个i，他有可能并不存在这个堆中
    // 我们需要对这个i进行一定的检查来防止数组越界的问题
    // 这里需要注意的是,我们不能仅仅让这个i大于等于1，小于等于capacity就说它是一个合法的i
    // 因为我们这个函数要做的是将i这个索引的元素修改成newItem,所以我们首先需要保证i这个索引位置的元素
    // 它真的存在在这个堆中，这里要注意，i这个索引在容量范围里，不代表这个索引就在堆中
    // 因为很容易想到我们之前的删除堆顶元素的操作，在删除一个堆顶元素后，并没有改变原始数组的大小，而是将堆的范围变小
    // 为此我们新编写一个函数，叫做 contain 用于判断我们当前这个索引堆真的包含i这个索引
    assert(contain(i + 1));
    // 同样，对于用户来说它使用的索引是从0开始的，但是我们类里的是从1开始的，所以这里要+1
    // 然后才能继续进行下面的操作。

    // 外部用户从0开始索引，在堆内部是从1开始，所以这里+1改为从1开始索引
    i += 1;

    data[i] = newItem;

    // 这么维护改变data值后索引堆的定义？
    // 很简单，我们只需要对data[i]这个元素的索引进行一下shiftUp和shiftDown操作
    // （也就是尝试堆这个索引进行一下向上挪和向下挪的操作）
    // 但是这里注意，如果我们需要正确的进行shiftUP和shiftDown操作，我们就需要找到正确的
    // data[i]这个i节点所在索引堆indexes中的索引值
    // 也就是找到 indexes[j] = i; 那么j就是data[i]在索引堆中的位置
    // 找到这个j之后，就可以很简单的指向shiftUp(j)和shiftDown(j)

    // 那怎么找到这个j呢？最简单的方法就是for循环遍历一遍indexes数组
    // for(int j = 1; j<= count; j++)
    // {
    //     if(indexes[j] == i)
    //     {
    //         shiftDown(j);
    //         shiftUp(j);
    //         return;
    //     }
    // }
    // 这样一来我们就将i这个索引的data修改为了新的item，同时维护了我们索引堆的性质

    // 这里分析一下这个 change 的时间复杂度
    // 首先我们需要将indexes遍历一遍，这个时间复杂度是O(n)
    // 然后下面的shiftDown和shiftUp 操作是O(log n)
    // 所以这里这个函数的时间复杂度他最差是O（n + log n）级别的
    // 也就是一个O(n)级别的函数

    // 通过上面引入了reverse这个数组后，我们就不需要继续遍历一遍这个数组了
    shiftDown(indexes[reverse[i]]);
    shiftUp(indexes[reverse[i]]);

    // 通过这两个语句可以看出来，我们直接通过索引定位的方式就找到了i这个索引所在的堆中的位置
    // 这个时间复杂度是O(1)
    // 所以这么一改动之后，我们这整个change操作变成了logn级别
    // 加入了反向查找的技术，我们的性能得到了巨大的提升。
  }
};

#endif