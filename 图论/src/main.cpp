#include <iostream>
#include <stdlib.h>
#include <vector>
#include "DenseGraph.h"
#include "SparseGraph.h"
#include "ReadGraph.h"
#include "Component.h"

using namespace std;

int main()
{
  // 邻接矩阵（Adjacency Matrix）
  // 邻接矩阵适合表示一个稠密的图（Dense Graph）,边相对较多

  // 邻接表（Adjacency Lists）
  // 邻接表适合表示稀疏的图（Sparse Graph），边相对较少

  // 单纯从边的多少来判断它是一个稀疏图还是稠密图有点抽象，
  // 如果一个节点和它连接的边远远小于能够与它连接的边的个数，就是稀疏图
  // 稠密图和完全图，完全图就是只所有节点都和其他节点都相互连接

  // 借助迭代器实现遍历某一个节点有几条邻边
  // 使用迭代器我们可以掩藏迭代的过程，按照一定的顺序访问一个容器中的所有元素
  // 也就是制作一个 图 中的迭代器，来实现访问一个指定节点它所有的相邻节点

  int N = 20;  // 节点数
  int M = 100; // 边数

  srand(time(NULL));
  // srand函数是随机数发生器的初始化函数。
  // 原型：void srand(unsigned seed);
  // 用法：它需要提供一个种子，这个种子会对应一个随机数，
  // 如果使用相同的种子, 后面的rand() 函数会出现一样的随机数。

  // 稀疏图 （Sparse Graph）
  SparseGraph g1(N, false);   // 生成一个稀疏图（无向的稀疏图）
  for (int i = 0; i < M; i++) // 循环M次，每次都随机生成一个节点 a,b 然后将a, b组成一条边添加到图中
  {
    int a = rand() % N;
    int b = rand() % N;
    g1.addEdge(a, b);
  }

  std::cout << "-----------稀疏图 （Sparse Graph）-------------" << std::endl;

  // 将这个图中每一个节点的邻边都打印出来
  for (int v = 0; v < N; v++)
  {
    std::cout << v << " : ";
    SparseGraph::adjIterator adj(g1, v);
    for (auto w = adj.begin(); !adj.end(); w = adj.next())
    {
      std::cout << w << " ";
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;

  // 时间复杂度 O(E)  E是稀疏图的边的条数
  // -----------稀疏图 （Sparse Graph）-------------
  // 0 : 9 1 15 2 16 11 10 5 2 16 11
  // 1 : 5 16 16 0 7 18 9 4 2 17 12 4
  // 2 : 9 9 0 1 5 19 17 9 11 0 17 15 14
  // 3 : 4 19 16 7 16
  // 4 : 3 9 8 19 15 9 1 14 12 1
  // 5 : 1 15 17 2 0 9
  // 6 : 17 15 9 10 15 10 14 18 8 10 12
  // 7 : 3 1 14 15 10 17 10 10 8
  // 8 : 18 18 18 4 13 11 7 6
  // 9 : 0 6 4 2 12 17 12 2 1 4 13 2 15 5 14
  // 10 : 6 12 6 7 7 0 7 15 13 6 12
  // 11 : 19 16 18 17 12 17 0 8 2 18 0
  // 12 : 9 10 9 12 11 18 13 16 4 1 10 6
  // 13 : 16 15 8 13 16 9 12 18 10
  // 14 : 7 6 4 2 9
  // 15 : 5 6 18 6 4 0 7 13 9 10 2
  // 16 : 1 11 1 3 13 13 0 3 12 0
  // 17 : 6 18 11 9 19 5 11 7 2 2 1
  // 18 : 17 15 11 8 8 8 1 12 6 13 19 11
  // 19 : 3 11 4 17 2 18

  // 稠密图 （Dense Graph）
  DenseGraph g2(N, false);
  for (int i = 0; i < M; i++)
  {
    int a = rand() % N;
    int b = rand() % N;
    g2.addEdge(a, b);
  }

  std::cout << "-----------稠密图 （Dense Graph）-------------" << std::endl;

  for (int v = 0; v < N; v++)
  {
    std::cout << v << " : ";
    DenseGraph::adjIterator adj(g2, v);
    for (int w = adj.begin(); !adj.end(); w = adj.next())
    {
      std::cout << w << " ";
    }
    std::cout << std::endl;
  }

  // 时间复杂度 O(V^2) V是稠密图的顶点个数
  // -----------稠密图 （Dense Graph）-------------
  // 0 : 1 3 4 5 7 8 10 12 13 15 16 19
  // 1 : 0 2 7 8 12 13 14 15
  // 2 : 1 3 10 11 15 16 18
  // 3 : 0 2 3 6 11 12 14 16 18
  // 4 : 0 9 10 12 14 15 17 18
  // 5 : 0 6 10 11 12 14 17 18
  // 6 : 3 5 8 14 16 17
  // 7 : 0 1 8 9 12 14 15 19
  // 8 : 0 1 6 7 10 13 18 19
  // 9 : 4 7 10 12 15 18
  // 10 : 0 2 4 5 8 9 10 13 18 19
  // 11 : 2 3 5 11 15 17 18 19
  // 12 : 0 1 3 4 5 7 9 16 19
  // 13 : 0 1 8 10 15 17
  // 14 : 1 3 4 5 6 7 17
  // 15 : 0 1 2 4 7 9 11 13 18 19
  // 16 : 0 2 3 6 12 16 17
  // 17 : 4 5 6 11 13 14 16 19
  // 18 : 2 3 4 5 8 9 10 11 15 19
  // 19 : 0 7 8 10 11 12 15 17 18

  // 从运行结果来看，我们的稠密图和稀疏图，遍历节点邻边的代码都是一样的（除了图类型名不一样外）
  // 此外，在稀疏图中我们能明显看到平行边的存在（一个节点中有多个相同的邻边节点）
  // 但是在稠密图中不存在这样的情况（就是因为我们使用邻接矩阵来实现稠密图已经自动将平行边问题给处理了）

  // 但是与此同时，对于稀疏图来说，遍历临边他的时间复杂度 是 O(E)；
  // 也就是对于稀疏图来说，我们有多少个边我们就遍历了多少次
  // 而在稠密图中，他的时间复杂度是 O(V^2), 是因为在我们实现的稠密图的迭代器中，已经对所有的顶点进行了一次遍历
  // 再加上外面这层循环，一共是两层循环 ，所以是O(V^2)

  // 同时我们使用迭代器来实现邻边遍历还有一个好处是，我们将稀疏图和稠密图的邻边遍历过程给屏蔽了
  // 从使用者的角度来看，这两个图他们的遍历方式都是一样的
  // 这就为我们后续实现图相关的算法带来了方便，因为后续我们的算法要求对稀疏图和稠密图都同时成立
  // 因为我们调用的都是同一个接口（我们的图算法都将封装在模板类中，这个模板类我们就可以任意的传入稀疏图或者稠密图）

  std::cout << "------------------------------------------------------------------------------------" << std::endl;

  string filename1 = "testG1.txt";

  // 稀疏图(13个节点的无向图)
  SparseGraph gg1(13, false);
  // 将filename1中的内容读进g1中
  ReadGraph<SparseGraph> read1(gg1, filename1);

  gg1.show();
  // vertex0:        5       1       2       6
  // vertex1:        0
  // vertex2:        0
  // vertex3:        4       5
  // vertex4:        3       6       5
  // vertex5:        0       4       3
  // vertex6:        4       0
  // vertex7:        8
  // vertex8:        7
  // vertex9:        12      10      11
  // vertex10:       9
  // vertex11:       12      9
  // vertex12:       9       11

  std::cout << "..............................." << std::endl;

  // 稠密图（13个节点的无向图）将filename1读为一个稠密图
  DenseGraph gg2(13, false);
  ReadGraph<DenseGraph> read2(gg2, filename1);

  gg2.show();
  // 0       1       1       0       0       1       1       0       0       0       0       0       0
  // 1       0       0       0       0       0       0       0       0       0       0       0       0
  // 1       0       0       0       0       0       0       0       0       0       0       0       0
  // 0       0       0       0       1       1       0       0       0       0       0       0       0
  // 0       0       0       1       0       1       1       0       0       0       0       0       0
  // 1       0       0       1       1       0       0       0       0       0       0       0       0
  // 1       0       0       0       1       0       0       0       0       0       0       0       0
  // 0       0       0       0       0       0       0       0       1       0       0       0       0
  // 0       0       0       0       0       0       0       1       0       0       0       0       0
  // 0       0       0       0       0       0       0       0       0       0       1       1       1
  // 0       0       0       0       0       0       0       0       0       1       0       0       0
  // 0       0       0       0       0       0       0       0       0       1       0       0       1
  // 0       0       0       0       0       0       0       0       0       1       0       1       0

  std::cout << "------------------------------------------------------------------------------------" << std::endl;

  string filename2 = "testG2.txt";

  SparseGraph graph1 = SparseGraph(13, false);
  ReadGraph<SparseGraph> readG1(graph1, filename1);
  Component<SparseGraph> component1(graph1);
  std::cout << "图 TestG1.txt 的连通分量是：" << component1.count() << std::endl;
  // 图 TestG1.txt 的连通分量是：3

  std::cout << std::endl;

  SparseGraph graph2 = SparseGraph(7, false);
  ReadGraph<SparseGraph> readG2(graph2, filename2);
  Component<SparseGraph> component2(graph2);
  std::cout << "图 TestG2.txt 的连通分量是：" << component2.count() << std::endl;
  // 图 TestG2.txt 的连通分量是：1

  std::cout << "在图 testG1.txt中，节点 7 和 节点 11 是否相连？\t" << component1.isConnected(7, 11) << std::endl;
  // 在图 testG1.txt中，节点 7 和 节点 11 是否相连？ 1
  return 0;
}