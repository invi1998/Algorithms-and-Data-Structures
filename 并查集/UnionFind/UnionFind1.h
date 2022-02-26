#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <iostream>
#include <cassert>

namespace UF1
{

  class UnionFind
  {

  private:
    int *id;   // 对于这个并查集，它用于表示数据的方式，是使用一个数组
    int count; // 当前这个UnionFind有多少个元素

  public:
    // 该构造函数需要用户传入一个n，表示单前这个并查集有多少元素
    UnionFind(int n)
    {
      count = n;
      id = new int[n];

      // 在初始情况下，每一个元素都是自己一个独立的组
      // 所以这里初始化的时候，让id的每一个元素都等于i，换句话说，没有任何两个值他们的id是相同的，也就是初始的时候没有任何两个元素连接在一起
      for (int i = 0; i < n; i++)
      {
        id[i] = i;
      }
    }

    ~UnionFind()
    {
      delete[] id;
    }

  public:
    int find(int p)
    {
      assert(p >= 0 && p < count);
      return id[p];
    }

    bool isConnected(int p, int q)
    {
      return find(p) == find(q);
    }

    void unionElements(int p, int q)
    {
      assert(p >= 0 && p < count);
      assert(q >= 0 && q < count);
      // 首先用find（o）来找到p相对应的id，用find（q）来找到q的id
      int pID = find(p);
      int qID = find(q);
      if (pID == qID)
      {
        // 说明这两个元素已经是相连的了
        return;
      }

      // 这里我们从头到尾扫描了一遍整个数组，所以他的时间复杂度是O(n)级别的
      for (int i = 0; i < count; i++)
      {
        if (id[i] == pID)
        {
          id[i] = qID;
        }
      }
    }
  };

}

#endif