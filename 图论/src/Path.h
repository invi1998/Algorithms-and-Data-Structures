//
// 寻路算法
//

#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <cassert>
#include <vector>
#include <stack>

using namespace std;

template <typename Graph>
class Path
{
private:
  Graph &G;
  int s; // 本类的原点
  bool *visited;
  int *from;
  // from这个数组存储的就是我们每访问到一个节点，就需要存储一下我们所访问到的这个节点是从哪个节点遍历过来的
  // 根据from这个数组我们就能倒推出两个节点之间相应的路径

private:
  void dfs(int v)
  {
    visited[v] = true;
    typename Graph::adjIterator adj(G, v);
    for (int i = adj.begin(); !adj.end(); i = adj.next())
    {
      // 这里深度优先遍历的算法和之前的大致都是一样的
      // 唯一不同的是我们这里要在遍历过程中维护一个from路径数组

      // 我们遍历V这个节点它所有相邻的节点，一旦发现它相邻的节点没有被访问过
      // 我们就将去 dfs 遍历这个相邻的i节点
      if (!visited[i])
      {
        // 在真正的进入i节点之前，那么就把这个 from[i]的值设置为 v
        from[i] = v;
        // 这样也就是说，我们访问的i这个节点是从v这个节点过来的
        dfs(i);
      }
    }
    // 至此，我们就通过一次dfs的过程，就将和s相邻接的所有的点相应的from的值给设置完成了
  }

public:
  Path(Graph &graph, int s) : G(graph)
  {
    // 算法初始化
    assert(s >= 0 && s < G.V());

    visited = new bool[G.V()];
    from = new int[G.V()];

    for (int i = 0; i < G.V(); i++)
    {
      visited[i] = false;
      from[i] = -1;
    }

    this->s = s;

    // 寻路算法
    dfs(s);
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
    // 回答这个问题，只需要返回visted[w]是否为true就可，
    // 因为只要w被遍历到，就说明从s到w有路径
    return visited[w];
  }

  // 原点s到w的具体路径是怎样的？将路径存储到一个vector容器向量中中
  void path(int w, std::vector<int> &vec)
  {
    // 如何获取从s到w的路径？
    // 其实有了from这个数组，我们只需要在from数组中从w这个点倒着推回去就可以
    // 然后由于这个过程是一个倒推的过程，所以我们将这个倒推的节点放在一个 stack 中
    // 最后再从这个stack取回到我们的vector中

    std::stack<int> ss; // 声明一个stack容器

    // 从 w 开始推，将w赋给一个新的变量 p
    int p = w;

    while (p != -1)
    {
      // while 循环，只要每次我们的p不等于 -1,那么就把这个 p 入栈到 ss中
      ss.push(p);
      // 然后p等于from[p]
      // 这里很好理解，比如from里存的是 2  3  6  1
      // 代表的就是 0 -> 2 ,1 -> 3, 2 -> 6
      // 其实也就是from这个数组里存的信息就是他每个下标代表的节点是从哪个节点（这个下标保存的那个数节点）过来的
      p = from[p];
    }
    // 这里就是我们从 w开始往回推，直到推到原节点（s），因为我们从来没有给源节点sfrom赋值过
    // 他都是原节点 from 的值一直都是 -1
    // 这样一来我们的从 s->w的路径就以倒叙的方式存到了stack中

    // 然后下面要做的事就是将stack中的数据取出来放到vector中
    // 为了安全起见，这里先对vector进行清空
    vec.clear();

    while (!ss.empty())
    {
      vec.push_back(ss.top()); // 将栈顶元素放入容器中
      ss.pop();                // 将栈顶元素出栈
    }
  }

  // 将路径进行打印输出
  void showPath(int w)
  {
    // 路径打印只需要遍历这个容器即可
    vector<int> vec;

    path(w, vec);
    for (auto iter = vec.begin(); iter != vec.end(); ++iter)
    {
      std::cout << *iter;

      // 平淡单前是否是容器的最后一个元素
      if (iter == vec.end() - 1)
      {
        // 最后一个元素打印一个回车
        std::cout << std::endl;
      }
      else
      {
        // 不是最后一个元素打印一个 ->
        std::cout << " -> ";
      }
    }
  }
};

#endif