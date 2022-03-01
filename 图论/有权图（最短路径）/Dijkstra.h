#ifndef __DIJKSTRA_H__
#define __DIJKSTRA_H__

#include "Edge.h"
#include "IndexMinHeap.h"
#include <iostream>
#include <stack>
#include <vector>

template <class Graph, class Weight>
class Dijkstra
{

private:
  Graph &G; // 图的引用
  int s;    // 单源最短路径的 源

  // 首先，我们从源点s到每一个节点最终他的最短距离是多少保存在这份数组中
  Weight *distTo;
  // 我们是一步一步的逐个找到每个节点的单源最短路径
  // 那么对于已经找到最短路径的顶点需要做一个标记，这个标记就保存在这个数组中
  bool *marked;
  // 我们这个算法，不但能求出到每一个顶点的单源最短路径权值，还能得到具体的最短路径是谁，这个最短路径就保存在这个容器中
  // from用来记录到达的每一个节点，到的这个节点它是从哪一个节点过来的
  std::vector<Edge<Weight> *> from;

public:
  Dijkstra(Graph &graph, int s) : G(graph)
  {
    this->s = s;
    distTo = new Weight[G.V()];
    marked = new bool[G.V()];

    for (int i = 0; i < G.V(); i++)
    {
      distTo[i] = Weight();
      marked[i] = false;
      from.push_back(nullptr);
    }

    IndexMinHeap<Weight> ipq(G.V());

    // Dijkstra
  }

  ~Dijkstra()
  {
    delete[] distTo;
    delete[] marked;
  }
};

#endif