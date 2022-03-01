#ifndef MINIMUMSPANTREE_DENSEGRAPH_H
#define MINIMUMSPANTREE_DENSEGRAPH_H

#include <iostream>
#include <cassert>
#include <vector>
#include "Edge.h"

using namespace std;

// 稠密图 - 邻接矩阵
template <typename Weight>
class DenseGraph
{
private:
  int n, m;
  bool directed;
  std::vector<vector<Edge<Weight> *>> g;

public:
  DenseGraph(int n, bool directed)
  {
    this->n = n;
    this->m = 0;
    this->directed = directed;
    for (int i = 0; i < n; i++)
    {
      // 这里图类中的二维容器里存的也不再是之前那种简单的bool类型，而是变成一个Edge<Weight>*
      // 这样一个指针类型，为什么存指针，就是为了方便表达NULL
      // 所以在初始的时候，初始值就不该是false了，而是一个NULL空值
      g.push_back(vector<Edge<Weight> *>(n, NULL));
    }
  }

  ~DenseGraph()
  {
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (g[i][j] != NULL)
        {
          delete g[i][j];
        }
      }
    }
  }

  int V()
  {
    return n;
  }

  int E()
  {
    return m;
  }

  // 这里添加边的操作对比之前无权图，新增了一个weight权值参数
  void addEdge(int v, int w, Weight weight)
  {
    assert(v >= 0 && v < n);
    assert(w >= 0 && w < n);

    if (hasEdge(v, w))
    {
      // 这样写完之后，保不齐在创建这个稠密图的时候，会来重复的边
      // 对于重复边的处理，不同的应用有不同的处理，
      // 这里使用一个简单的处理方式，就是让新的重复的边再稠密图中直接覆盖掉旧的边

      // 这里覆盖的方式就是如果我发现 [v][w] 这里已经有边了的话，
      // 那么就直接delete掉原先的g[v][w]的边，如果是无向图那么还应该把g[w][v]也delete掉
      delete g[v][w];
      if (!directed)
      {
        delete g[w][v];
      }
      // 边数--
      m--;
      // 然后这里就不能在return了，而是应该继续玩下走，去把这个新重复边添加上去

      // 这里额外说一下，在一些具体的业务处理逻辑中，对于重复的边，
      // 处理方式可能会是按照边权值的大小等具体的业务逻辑来决定保留那一条边，这里就没这样做
      // 所以，具体业务具体分析，可以根据需要来修改这个函数
    }

    g[v][w] = new Edge<Weight>(v, w, weight);
    if (!directed)
    {
      // 如果是无向图
      g[w][v] = new Edge<Weight>(w, v, weight);
    }
    m++;
  }

  bool hasEdge(int v, int w)
  {
    assert(v >= 0 && v < n);
    assert(w >= 0 && w < n);

    return g[v][w] != NULL;
  }

  void show()
  {
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (g[i][j])
        {
          std::cout << g[i][j]->wt() << "\t";
        }
        else
        {
          std::cout << "NULL \t";
        }
      }
      std::cout << std::endl;
    }
  }

public:
  // 迭代器嵌套类(迭代给定节点v的相邻节点)
  class adjIterator
  {
  private:
    DenseGraph &G;
    int v;
    int index;

  public:
    adjIterator(DenseGraph &graph, int v) : G(graph)
    {
      this->v = v;
      this->index = -1;
    }

    Edge<Weight> *begin()
    {
      index = -1;
      return next();
    }

    Edge<Weight> *next()
    {
      for (index += 1; index < G.V(); index++)
      {
        if (G.g[v][index])
        {
          return G.g[v][index];
        }
      }
      return NULL;
    }

    bool end()
    {
      return index >= G.V();
    }
  };
};

#endif