//
// 寻路算法
//

#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

template <typename Graph>
class Path
{
private:
  Graph &G;
  int s;
  bool *visited;
  int *from;
  // from这个数组存储的就是我们每访问到一个节点，就需要存储一下我们所访问到的这个节点是从哪个节点遍历过来的
  // 根据from这个数组我们就能倒推出两个节点之间相应的路径

public:
  Path(Graph &graph, int s) : G(graph)
  {
    // 算法初始化
    assert(s >= 0 && s < G.V())

        visited = new bool[G.V()];
    from = new int[G.V()];

    for (int i = 0; i < G.V(); i++)
    {
      visited[i] = false;
      from[i] = -1;
    }

    this->s = s;

    // 寻路算法
  }

  ~Path()
  {
    delete[] visited;
    delete[] from;
  }

  // 对于这个类，我们可以设置3个函数

  // 首先我们可以判断这个类的原点s到我们给定的一个节点w是否有路径？
  bool hasPath(int w)
  {
  }

  // 原点s到w的具体路径是怎样的？将路径存储到一个vector容器中
  void path(int w, std::vector<int> &vec)
  {
  }

  // 将路径进行打印输出
  void showPath(int w)
  {
  }
};

#endif