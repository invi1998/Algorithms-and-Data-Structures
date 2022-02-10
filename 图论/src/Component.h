//
// 求一个图的连通分量
//

#ifndef GRAHPH_COMPONENT_H
#define GRAHPH_COMPONENT_H

#include <iostream>
#include <cassert>

using namespace std;

template <typename Graph>
class Component
{
private:
  Graph &G;      // 存储图
  bool *visited; // bool型的数组，用来保存是否被访问过
  int ccount;    // 记录有多少个连通分量

  // 至此，我们已经可以计算出我们的图中有多少个连通分量，那么有了连通分量，
  // 我们就可以很容易的计算出两个节点之间是否是相连的

  bool *id; // 该数组用于保存两个节点之间是否是想邻的（相邻的节点他们的id取一样的值，而不相邻的节点他们的id不相同）

private:
  // 深度优先遍历函数
  void dfs(int v)
  {
    // 每次我对V这个节点进行dfs遍历，其实也就是相当于我们遍历到了这个节点
    // 那么visited[v]就先给他置为true
    visited[v] = true;

    // 对于判断两个节点是否相邻
    // 由于初始的时候ccound = 0，所以在第一次运行dfs的时候，
    // 我们只需要将遍历到的所有的点他相应的id设置为ccount的值即可
    // 表示在这次深度遍历到的所有的点都是属于同一个连通分量里的（也就是都是相邻的）
    id[v] = ccount;

    // 之后我们要看的就是与V相邻的所有的节点，哪个节点没有被访问过，我们就接着去访问哪个节点
    // 这里就用到我们之前设计的对于Graph的迭代器
    // Graph::adjIterator adj(G, v);   // 编译报错 error: need ‘typename’ before ‘Graph::adjIterator’ because ‘Graph’ is a dependent scope
    typename Graph::adjIterator adj(G, v); // 遍历G这张图，v这个节点它
    // 这里有个小陷阱，如果直接这样写，那么C++编译器并不知道这个adjIterator它是一个类型还是一个函数
    // 为了显示的高数编译器这是一个类型，我们可以在前面显示的添加一个typename关键字

    // 然后使用for循环查看v所有的邻边
    for (int i = adj.begin(); !adj.end(); i = adj.next())
    {
      // 然后判断在这个循环中获得的这个相邻的节点，他的visited[i]是否为false
      // 如果为false表示它没有被访问过，那么我们接着继续去dfs这个节点
      if (!visited[i])
      {
        dfs(i);
      }
      // 这里使用了递归的方式来实现深度遍历
    }
  }

public:
  Component(Graph &graph) : G(graph)
  {
    // 为数组分配内存空间，有多少个节点就开辟多少个空间
    visited = new bool[G.V()];
    id = new bool[G.V()];
    ccount = 0;

    // 将数组每一个元素都初始化为 false，表示初始时候每一个节点都没有被访问过
    for (int i = 0; i < G.V(); i++)
    {
      visited[i] = false;
      id[i] = -1;
    }

    // 具体的深度优先遍历算法
    for (int i = 0; i < G.V(); i++)
    {
      // 如果我单前正在遍历的这个节点他没有被访问过的话
      if (!visited[i])
      {
        // 没有被访问过，那就对单前节点进行一次深度优先遍历
        dfs(i);
        // 这个深度优先遍历的过程，他可以将i和与i相邻接的所有节点遍历到
        // 那么没有遍历到的节点一定就在另外的一个连通分量中
        // 所以这里连通分量++
        ccount++;
        // 然后++之后我们继续进行循环
        // 可以想象到，在这次循环中，在之前dfs遍历过的所有节点他的visited[i]都为true
        // 而没有被遍历的节点一定存在另外的一个连通分量中
        // 我们在进行dfs遍历，以此类推
        // 使用这样的过程我们就将这个图中的所有节点都遍历了以便
        // 同时我们还用ccount来记录了连通分量
      }
    }
  }

  ~Component()
  {
    // 因为我们在构造函数中开辟了内存空间，相应的就该在析构函数中进行释放
    delete[] visited;
    delete[] id;
  }

public:
  // 返回图的连通分量
  int count()
  {
    return ccount;
  }

  // 判断两个节点之间是否是相邻的
  bool isConnected(int v, int w)
  {
    // 这里为了严谨，也应该检查一下传递进来的参数是否越界
    assert(v >= 0 && v < G.V());
    assert(w >= 0 && w < G.V());
    return id[v] == id[w];
  }
};

#endif