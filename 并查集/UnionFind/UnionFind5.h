#ifndef UNION_FIND_5_H
#define UNION_FIND_5_H

#include <iostream>
#include <cassert>

namespace UF5
{

  class UnionFind
  {

  private:
    int *parent;
    int count;
    // 记录对于每一节点以他为根的那个集合的层数
    int *rank; // rank[i]就表示以i为根的集合中树的层数

  public:
    UnionFind(int n)
    {
      parent = new int[n];
      rank = new int[n];
      count = n;
      for (int i = 0; i < count; i++)
      {
        parent[i] = i;
        rank[i] = 1;
      }
    }

    ~UnionFind()
    {
      delete[] parent;
      delete[] rank;
    }

  public:
    int find(int p)
    {
      assert(p >= 0 && p < count);
      // find操作就是不断的通过p索引追溯他的父亲节点，知道他的父亲节点等于自身
      while (parent[p] != p)
      {
        // 将p这个节点指向父亲的这个指针，指向p这个节点它父亲的父亲
        parent[p] = parent[parent[p]]; // 路径压缩过程

        // 路径压缩完成之后，继续让p = parent[p]，继续进行下一轮的检查
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
        if (rank[pRoot] < rank[qRoot])
        {
          parent[pRoot] = qRoot;
        }
        else if (rank[pRoot] > rank[qRoot])
        {
          parent[qRoot] = pRoot;
        }
        else // rank[pRoot] == rank[qRoot]
        {
          // 在这种情况下，谁指向谁并不重要，重要的是要根据指向情况，维护rank
          parent[pRoot] = qRoot;
          rank[qRoot] += 1;
        }
      }
    }
  };

}

#endif