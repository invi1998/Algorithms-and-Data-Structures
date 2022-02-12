//
// 使用广度优先算法来求一个无权图的最短路径
//

#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <stack>

using namespace std;

template <typename Graph>
class ShortestPath
{
private:
  Graph &G;
  int s;
  bool *visited;
  int *from;
  int *ord; // 这个节点记录的是从原节点s到每一个节点的最短距离是多少

public:
  ShortestPath(Graph &graph, int s) : G(graph)
  {
    // 算法初始化
    assert(s >= 0 && s < graph.V());

    visited = new bool[graph.V()];
    from = new int[graph.V()];
    ord = new int[graph.V()];

    for (int i = 0; i < graph.V(); i++)
    {
      visited[i] = false;
      from[i] = -1;
      ord[i] = -1;
    }

    this->s = s;

    // 该队列用于辅助求无向图的最短路径（辅助队列）
    std::queue<int> q;

    // 无向图最短路径算法

    // 先将原点s推入到辅助队列q中
    q.push(s);
    // s推入到辅助队列后，就表示以后再遍历遇到s这个点，我就都不需要再次入队了，
    // 所以这里将visited[s]设置为true
    visited[s] = true;
    // 与此同时我们也需要更新一下ord[s] = 0；表示s -> s的距离为0
    ord[s] = 0;

    // 下面我们开始循环
    // 对于整个循环来说，只要辅助队列q不为空，就需要一直循环操作下去
    while (!q.empty())
    {
      // 在每次循环过程中，我们首先先将辅助队列首的元素取出来
      int v = q.front();
      // 然后就可以将队列首的元素移除出队列
      q.pop();

      // 然后拿到队列首的元素后，下一步我们需要做的就是使用迭代器遍历它所有相邻的节点元素
      typename Graph::adjIterator adj(G, v); // G这张图中v节点的所有相邻元素
      for (auto iter = adj.begin(); !adj.end(); iter = adj.next())
      {
        // 我们拿到iter这个节点，我们首先要做的就是判断这个节点有没有被访问过
        if (!visited[iter])
        {
          // 没有被访问过，加入到辅助队列中
          q.push(iter);
          // 同时加入到队列之后，就表示这个节点被访问过了，那就需要将他的visited[iter]设置为true
          visited[iter] = true;
          // 同时我们还应该在这里维护更新from这个数组，表示iter这个节点是从v这个节点过来的
          from[iter] = v;
          // 最后不要忘记在求最短距离的时候，设置的这个ord数组
          // 对于ord[iter],也就是对于iter这个节点它到s的最短路径应该是从它的遍历过来的及节点 v 到s的最短路径 + 1
          ord[iter] = ord[v] + 1;
        }
      }
    }
    // 至此我们就使用了广度优先的原则对图G从原点s进行了遍历
  }

  ~ShortestPath()
  {
    delete[] from;
    delete[] visited;
    delete[] ord;
  }

public:
  // 对于无权图来说，用户可以查询的信息和之前深度优先算法可查询的信息都是一样

  // 查询从原节点s到w是否有路径？
  bool hasPath(int w)
  {
    assert(w >= 0 && w < G.V());
    return visited[w];
  }

  // 求节点s到w的最短路径，并将其存到容器vec中
  void path(int w, vector<int> &vec)
  {
    assert(w >= 0 && w < G.V());

    std::stack<int> ss;

    int p = w;

    while (p != -1)
    {
      ss.push(p);
      p = from[p];
    }

    vec.clear();

    while (!ss.empty())
    {
      vec.push_back(ss.top());
      ss.pop();
    }
  }

  // 打印输出从s到w的最短路径
  void showPath(int w)
  {
    assert(w >= 0 && w < G.V());

    vector<int> vec;
    path(w, vec);
    for (auto iter = vec.begin(); iter != vec.end(); ++iter)
    {
      std::cout << *iter;
      if (iter == vec.end() - 1)
      {
        std::cout << std::endl;
      }
      else
      {
        std::cout << " -> ";
      }
    }
  }

  // 返回s到w的最短路径长度
  int length(int w)
  {
    assert(w >= 0 && w < G.V());

    return ord[w];
  }
};

#endif