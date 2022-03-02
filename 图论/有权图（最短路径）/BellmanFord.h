// Bellman-Ford (贝尔曼-福特)算法实现

#ifndef __BELLMAN_FORD_H__
#define __BELLMAN_FORD_H__

#include "Edge.h"
#include <iostream>
#include <stack>
#include <vector>

template <class Graph, class Weight>
class BellmanFord
{

private:
  Graph &G;                    // 图的引用
  int s;                       // 起始点
  Weight *distTo;              // distTo[i]存储从起始点s到i的最短路径长度
  vector<Edge<Weight> *> from; // from[i]记录最短路径中, 到达i点的边是哪一条
                               // 可以用来恢复整个最短路径
  bool hasNegativeCycle;       // 标记图中是否有负权环

  // 遍历一遍所有的点，对每一个点的所有邻边再遍历一次，如果发现还有边没有访问过（换句话说就是还能进行松弛的话），
  // 就说明这个时候，图中就一定存在负权环
  bool detectNegativeCycle()
  {
    for (int i = 0; i < G.V(); i++)
    {
      typename Graph::adjIterator adj(G, i);
      for (Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next())
      {
        if (!from[e->w()] || distTo[e->v()] + e->wt() < distTo[e->w()])
        {
          return true;
        }
      }
    }
    return false;
  }

public:
  BellmanFord(Graph &graph, int s) : G(graph)
  {
    this->s = s;
    distTo = new Weight[G.V()];
    for (int i = 0; i < G.V(); i++)
    {
      from.push_back(nullptr);
    }

    // Bellman-Ford

    // 首先我们能够做的就是将distTo[s]这个s节点设置为初始值
    distTo[s] = Weight();

    // 接下来我们要做的就是对整张图中所有的点进行V-1次松弛操作。(所以这里从1开始)
    for (int pass = 1; pass < G.V(); pass++)
    {
      // 在这次循环中，堆所有的点的邻边进行松弛操作

      // Relaxation

      // 首先对所有的点进行一次遍历
      for (int i = 0; i < G.V(); i++)
      {
        // 遍历到每一个点之后，都要对每一个点进行一次遍历
        typename Graph::adjIterator adj(G, i);
        for (Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next())
        {
          // 遍历到这条邻边e之后，我们要做的就是看一下，如果我们绕道，绕到i这个节点，在去e的这个终点w
          // 是否比直接去e的这个终点w的距离还要小。
          // distTo[e->v()] 就代表现在找到的这个到达e->v()这个节点的距离，然后
          // 加上e这条边的权值e->wt()，就是我们绕道这个节点去e的终点w得到的权值
          // 然后将这个绕道的权值和之前直达e->w()的权值做比较，如果比他小，那么我们就应该做这次松弛操作
          // 同样的，这里也不要忘记，如果我们之前就没有访问过e这条边的对端w，那么这个时候也是需要进行一次松弛操作的，这里判断是否访问过e这条边的对端w，用from这个容器就可以判断，如果from[e->w()]有值，就说说明我们已经访问过w了
          if (!from[e->w()] || distTo[e->v()] + e->wt() < distTo[e->w()])
          {
            // 进行松弛操作
            // 首先我们需要更新一下e->w()这个节点的distTo信息，把它更新为从源点到e->v()这个节点的权值
            // 再加上e这条边的权值（也就是更新为我们松弛绕道的这条路径权值）
            distTo[e->w()] = distTo[e->v()] + e->wt();
            // 然后我们要更新一下from这个数组，更新为e这条边，也就是说我们是通过e这条边到达的e->w()这个节点
            from[e->w()] = e;
          }
        }
      }
    }

    // 我们整个Bellman-Ford算法就是这么简单，看起来是3重循环，实际上一个更好的理解就是对整个图的所有的节点进行V-1轮松弛操作
    // 经过这个过程，如果我们整个图中没有负循环的话，那么从源点s到其他所有节点的最短路径，就已经存在distTo这个数组中了
    // 而且从代码里也可以看到，因为我们的Bellman-Ford不像Dijkstra算法那样，需要每次取最小边的节点进行松弛，而是需要对所有节点无差别的V-1轮松弛，所以这里没有使用最小索引堆之类的辅助数据结构

    // 不过由于我们图可能还会有负循环,所以在最后我们为我们的hasNegative进行赋值
    // 这个赋值逻辑就是调用函数再对我们的图中所欲节点进行一次松弛操作。
    hasNegativeCycle = detectNegativeCycle();
  }

  ~BellmanFord() { delete[] distTo; }

  // 查询图中是否有负权环
  bool negativeCycle() { return hasNegativeCycle; }

  // 查询从源点s到节点w的单源最短路径权值
  Weight sortestPathTo(int w)
  {
    assert(w >= 0 && w < G.V());
    assert(!hasNegativeCycle);
    return distTo[w];
  }

  // 查询是否存在从源点s到节点w的单源最短路径
  bool hasPathTo(int w)
  {
    assert(w >= 0 && w < G.V());
    return from[w] != nullptr;
  }

  // 获得从节点s到节点w的最短路径，并保存在用户传入的参数vec中
  void sortestPath(int w, std::vector<Edge<Weight>> &vec)
  {
    assert(w >= 0 && w < G.V());
    assert(!hasNegativeCycle);

    std::stack<Edge<Weight> *> s;
    Edge<Weight> *e = from[w];

    while (e->v() != this->s)
    {
      s.push(e);
      e = from[e->v()];
    }

    s.push(e);

    while (!s.empty())
    {
      e = s.top();
      vec.push_back(*e);
      s.pop();
    }
  }

  // 打印从源点s到w的最短路径
  void showPath(int w)
  {
    assert(w >= 0 && w < G.V());
    assert(hasPathTo(w));
    assert(!hasNegativeCycle);

    std::vector<Edge<Weight>> vec;
    sortestPath(w, vec);
    for (auto iter = vec.begin(); iter != vec.end(); ++iter)
    {
      std::cout << (*iter).v() << " -> ";
      if (iter == vec.end() - 1)
      {
        std::cout << (*iter).w() << std::endl;
      }
    }
  }
};

#endif