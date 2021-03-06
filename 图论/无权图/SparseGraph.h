// 稀疏图

#ifndef GRAPH_SPARSEGRAPH_H
#define GRAPH_SPARSEGRAPH_H

using namespace std;

// 稀疏图-邻接表
class SparseGraph
{
private:
  int n, m;      // 点数 和 边数
  bool directed; // 表示有向图还是无向图
  vector<vector<int>> g;
  // 这里同样用一个二维容器来存储图中的边
  // 只不过这里元素的种类是 int 型，是因为邻接表g[i] 里面存储的就是和i这个顶点相邻的所有顶点编号

public:
  SparseGraph(int n, bool directed) : n(n), m(0), directed(directed)
  {
    for (int i = 0; i < n; i++)
    {
      g.push_back(vector<int>());
      // 初始化的时候，遍历这n个点，然后把每个点都push一个空int型vector
      // 表示初始化的时候，每一个顶点都没有与之相邻的顶点
    }
  }

  ~SparseGraph() {}

  int V() { return n; } // 该函数返回图中有多少个顶点
  int E() { return m; } // 该函数返回图中有多少条边

  void addEdge(int v, int w)
  {
    // 确保 v, w 不越界
    assert(v >= 0 && v < n);
    assert(w >= 0 && w < n);

    // 将 顶点 w push进g[v]中，表示 节点 v 与 w相连
    g[v].push_back(w);

    // 同样的判断该图是不是一个无向图，如果是无向图，那么还需要再添加一个 由 w 指向 v的节点连接
    // 同时这里还要注意一点，如果这条边时一个自环边（也就是自己和自己连接，v == w）
    // 那么就只需要执行上面那一条边添加就可以了
    if (v != w && !directed)
    {
      g[w].push_back(v);
    }

    m++;
  }

  bool hasEdge(int v, int w)
  {
    assert(v >= 0 && v < n);
    assert(w >= 0 && w < n);

    // 对于邻接表，我们怎么判断它是否存在一条由 V -> w 的边呢？
    // 这里对比与邻接矩阵，就会显得稍微复杂
    // 这里我们必须循环边里 节点 v的所有相邻的节点
    for (int i = 0; i < g[v].size(); i++)
    {
      // 然后依次判断个相邻节点，如果该节点 == w，就说明 v -> w相连
      if (g[v][i] == w)
      {
        return true;
      }
      return false;
    }

    // 所以从这里可以看到，这个邻接表的函数对比于邻接矩阵，他的时间复杂度在最差的情况下是O(n)级别的
    // 而邻接矩阵他的时间复杂度 是 O(1)；

    // 同样的如果我们在addEdge的时候如果要取消掉平行边（两条或者多条指向相同的边），
    // 那么就需要调用这个函数,那么添加边的函数他的时间复杂度也就变成了 O(n),
    // 所以，如果我们需要在 邻接表中取消平行边，是需要付出很大代价的

    // 所以，一般我们在绘制邻接表的时候，就不去管平行边问题了（也就是我们默认允许平行边存在）

    // 或者我们也可以在邻接表绘制完成后，在对这个图进行整体的遍历，然后将平行边处理掉（练习--）
    // todo
  }

public:
  // 打印图
  void show()
  {
    for (int i = 0; i < n; i++)
    {
      std::cout << "vertex" << i << ":\t";
      for (int j = 0; j < g[i].size(); j++)
      {
        std::cout << g[i][j] << "\t";
      }
      std::cout << std::endl;
    }
  }

public:
  // 在稀疏图这个类中实现一个新的类，表示一个相邻边的迭代器
  class adjIterator
  {
  private:
    SparseGraph &G; // 保存要迭代的图
    int V;          // 保存要迭代的顶点
    int index;      // 该变量用于指示迭代到哪里了

  public:
    // 对于构造函数，这里我希望用户高数迭代器两个内容
    // graph 表示我们要迭代的是那张图
    // v 表示用户要迭代的是哪一个顶点 他相邻的边
    adjIterator(SparseGraph &graph, int v) : G(graph), V(v), index(0)
    {
    }

    // 返回要迭代的第一个元素
    int begin()
    {
      int index = 0;
      // 对于begin这个函数，我们首先要检查对于G这个图
      // 他里面g[V]这个分量的size是否为0
      // 如果不为 0 ，那么我们就返回这个g[V]分量的第一个元素即可
      // 否者返回 -1 就行
      if (G.g[V].size())
      {
        return G.g[V][index];
      }
      return -1;

      // 这样我们就找到了v这个节点在这个图中的第一个相邻节点，如果没有的话返回的就是-1
    }

    // 从当前迭代的元素向下偏移找下一个元素
    int next()
    {
      index++;

      // 判断当前index值是否越界
      if (index < G.g[V].size())
      {
        return G.g[V][index];
      }
      return -1;
    }

    // 用于指示我们的迭代终止没有
    bool end()
    {
      return index >= G.g[V].size();
      // 如果迭代指示器 index 大于等于 单前向量g[v]的size，表示已经越界（对于g[v]这个分量来说已经迭代完成了）
    }
  };
};

#endif