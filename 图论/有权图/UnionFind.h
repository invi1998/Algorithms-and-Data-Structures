#ifndef __UNION_FIND_H__
#define __UNION_FIND_H__

#include <cassert>
#include <iostream>

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
    // find操作就是不断的通过p索引追溯他的父亲节点，直到他的父亲节点等于自身
    // while(parent[p] != p)
    //   {
    //     // 将p这个节点指向父亲的这个指针，指向p这个节点它父亲的父亲
    //     parent[p] = parent[parent[p]];  // 路径压缩过程

    //     // 路径压缩完成之后，继续让p = parent[p]，继续进行下一轮的检查
    //     p = parent[p];
    //   }

    // return p;

    // 进一步优化压缩路径

    // 如果当前的这个p不是一个根节点
    if (p != parent[p])
    {
      // 要注意这里的这个递归逻辑，这里find(parent[p])一定会指向p的根节点
      // 然后将parent[p]，p的父亲节点指向这个根节点
      // 那么在这个递归过程中所遍历到的每一个节点，他们的parent都会指向根节点
      parent[p] = find(parent[p]);
    }

    return parent[p];
  }

  bool isConnected(int p, int q) { return find(p) == find(q); }

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

#endif