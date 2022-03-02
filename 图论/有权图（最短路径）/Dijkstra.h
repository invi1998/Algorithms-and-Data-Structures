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
    assert(s >= 0 && s < G.V());
    this->s = s;
    distTo = new Weight[G.V()];
    marked = new bool[G.V()];

    for (int i = 0; i < G.V(); i++)
    {
      // 对于distTo的初始化，我们默认初始化为0，因为这里不知道权值Weight的具体类型是什么，所以这里调用模板参数Weight的默认构造函数进行初始化
      distTo[i] = Weight();
      marked[i] = false;
      from.push_back(nullptr);
    }
    // 声明一个最小索引堆（为其开辟图顶点个数那么大的内存空间）
    IndexMinHeap<Weight> ipq(G.V());

    // Dijkstra

    // 我们首先要做的事情就是对我们的源点s做一次初始化操作
    distTo[s] = Weight(); // 从源点到源点的距离一定为 0
                          // （不过如果权值是类类型，那么就是默认构成出来的初值）

    from[s] = new Edge<Weight>(s, s, Weight()); // 源点s到s自己的路径

    ipq.insert(s, distTo[s]);

    marked[s] = true; // 然后相应的s这个点就被我们访问过了，将其标记为true

    // 然后将s这个源点压入我们的最小索引堆中，然后s这个节点距离源点s的距离就是distTo[s];
    ipq.insert(s, distTo[s]);

    // 然后进行我们的循环，在这个循环中只要我们的最小索引堆中的元素还存在，它不为空的话，就进行这个循环
    while (!ipq.isEmpty())
    {
      // 在这个循环中，首先我们要做的就是找到这个最小索引堆中存在的元素中相应的离源点s最近的那个节点，把这个节点用v存储
      int v = ipq.extracMinIndex();

      // distTo[v]就是s到节点v的最短距离
      marked[v] = true; // 那么此时v这个节点就被访问过了，堆marked这个数组进行更新，将v这个节点进行标识

      // Relaxation (松弛操作)

      // 接下来要做的事情就是针对v这个节点进行一遍松弛操作（也就是看是否存在经过v这个节点进行中转到另外一个点 比 不经过v这个点直接到那个点的距离要小）
      // 所以堆v这个节点的松弛操作，我们就需要访问一下v这个节点的所有的邻边
      typename Graph::adjIterator adj(G, v);
      for (Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next())
      {
        int w = e->other(v); // 找到v这个节点的邻边e的对端端点 w
        // 如果这个对端端点w没有被标记过（也就是代表从源点s到w的最短路径我们还没有找到过的话），那么相应的我们就需要进行松弛的判断
        if (!marked[w])
        {
          // 如果w没有被访问过的话 （from[w] == nullptr）那么不用说要进行松弛操作
          // 或者如果w被访问过，那我们就需要比对一下经过v（也就是从源点s到v的距离distTo[v]）中转去访问w（也就是加上v到w的这条边的权值 e->wt() ）的路径权值是否小于直接访问w的权值 distTo[w],如果小于那么我们就需要进行松弛操作
          if (from[w] == nullptr || distTo[v] + e->wt() < distTo[w])
          {
            // 在这个松弛操作里，首先我们需要将源点s到达w的最短路径更新为我们松弛出来的这条路径
            distTo[w] = distTo[v] + e->wt();
            // 其次我们需要更新节点w的form信息，它是从v这个节点通过e这条边过来的
            from[w] = e;
            // 之后我们要维护一下我们的最小索引堆
            // 首先我们需要判断我们的最小索引堆中是否包含我们的w节点
            if (ipq.contain(w))
            {
              // 如果包含，那么我们就使用change函数来更新节点v及其对应的data值（也就是最小距离权值）
              ipq.change(w, distTo[w]);
            }
            else
            {
              // 否者的话，在我们的最小索引堆中还没有w节点信息，那么就使用insert函数添加
              ipq.insert(w, distTo[w]);
            }
          }
        }
      }
      // 通过这轮循环，我们就完成了节点v它所有邻边的松弛操作
    }
  }

  ~Dijkstra()
  {
    delete[] distTo;
    delete[] marked;
    delete from[s];
  }

  // 查询从源点s到节点w的最短路径权值
  Weight sortestPathTo(int w)
  {
    assert(w >= 0 && w < G.V());
    assert(hasPathTo(w));
    return distTo[w];
  }

  // 查询从源点s到节点w是否存在通路
  bool hasPathTo(int w)
  {
    assert(w >= 0 && w < G.V());
    return marked[w];
  }

  // 求从源点s到节点w的最短路径，并将最短路径保存到用户传进来的容器中
  void sortestPath(int w, std::vector<Edge<Weight>> &vec)
  {

    assert(w >= 0 && w < G.V());
    assert(hasPathTo(w));

    std::stack<Edge<Weight> *> s;
    Edge<Weight> *e = from[w]; // 将from中的数据（边）从w开始，以倒序的方式放进栈中
    while (e->v() != this->s)
    {
      s.push(e);
      e = from[e->v()];
    }

    s.push(e);

    // 将栈中的元素一个一个拿出来，放到用户传递进来的容器vec中，就得到了源点s到节点w的最短路径
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