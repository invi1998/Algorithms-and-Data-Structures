#ifndef UNION_FIND_3_H
#define UNION_FIND_3_H

#include <iostream>
#include <cassert>

namespace UF3
{

  class UnionFind
  {

  private:
    int *parent;
    int count;
    // 记录对于每一节点以他为根的那个集合的节点个数
    int *sz; // sz[i]就表示以i为根的集合中元素个数

  public:
    UnionFind(int n)
    {
      parent = new int[n];
      sz = new int[n];
      count = n;
      for (int i = 0; i < count; i++)
      {
        parent[i] = i;
        sz[i] = 1;
      }
    }

    ~UnionFind()
    {
      delete[] parent;
      delete[] sz;
    }

  public:
    int find(int p)
    {
      assert(p >= 0 && p < count);
      // find操作就是不断的通过p索引追溯他的父亲节点，知道他的父亲节点等于自身
      while (parent[p] != p)
      {
        p = parent[p];
      }

      return p;
    }

    bool isConnected(int p, int q)
    {
      return find(p) == find(q);
    }

    void unionElements(int p, int q)
    {

      int pRoot = find(p);
      int qRoot = find(q);
      if (pRoot != qRoot)
      {
        if (sz[pRoot] < sz[qRoot])
        {
          parent[pRoot] = qRoot;
          sz[qRoot] += sz[pRoot];
        }
        else
        {
          parent[qRoot] = pRoot;
          sz[pRoot] += sz[qRoot];
        }
      }
    }
  };

}

#endif