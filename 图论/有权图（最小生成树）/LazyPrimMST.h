#ifndef LAZY_PRIM_MST_H
#define LAZY_PRIM_MST_H

#include "Edge.h"
#include "MinHeap.h"
#include <iostream>
#include <vector>

template <typename Graph, typename Weight>
class LazyPrimMST
{

private:
  Graph &G;
  MinHeap<Edge<Weight>>
      pq; // 这个最小堆充当一个优先队列，在这个优先队列中，存储的是这个图中的边（确切的说是最小生成树的候选边）
  // 首先，我们在划分切分的时候，需要将我们的顶点一个一个的划分到另一边去，marked[i]表示这个点是否被标记了
  // 如果被标记了，就表示被划分到另外一个切分区去了（相当于文档中节点一个一个从蓝色变成了红色）
  bool *marked;
  // 除此之外，我们求出来的最下生成树就是就是一个一个边，我们将这些边放入到一个容器中
  // 在这个容器中，每一个元素都是Edge<Weight>这样的边类型
  std::vector<Edge<Weight>> mst;
  // 最后对于我们最小生成树的相应权值，我们用mstWeight来存储
  Weight mstWeight;

  void visit(int v)
  {
    // 我们访问v这个节点，首先我们得保证，v这个节点他是一个对应在文档里的蓝色节点
    // 也就是marked这个标记里没标记过这个节点
    assert(!marked[v]);
    // 之后访问到了这个节点，就把它的marked设置为true
    marked[v] = true;
    // 之后要做的就是遍历这个红色的节点他的所有临边（也就是v节点的所有邻边）
    typename Graph::adjIterator adj(G, v);
    for (Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next())
    {
      // 我们依次访问v这个节点的所有邻边，一旦我们发现，v这个节点他的邻边对应的另外一个节点，没有被marked标记上，那么这条邻边就是一个
      // 横切边
      if (!marked[e->other(v)])
      {
        // 找到了一条横切边，那么就意味着我们可以将这条边放入我们的堆中，作为我们的最小生成树的候选边
        pq.insert(*e);
      }
    }
  }

public:
  // 注意这里这个最小堆的初始化，这里给最小堆数组开的空间大小是这个图的边数这么大的空间（也就是说，在最差的情况下，我们的这个图中所有的边都会放进这个最小堆中）
  LazyPrimMST(Graph &graph) : G(graph), pq(MinHeap<Edge<Weight>>(graph.E()))
  {
    // 为marked开空间，空间大小是顶点个数
    marked = new bool[G.V()];

    // 给marked开辟好空间以后，我们给这个marked赋予初值
    for (int i = 0; i < G.V(); i++)
    {
      marked[i] = false;
    }
    mst.clear();

    // lazy prim
    // 首先我们visit(0)这个节点，也就是把0先marked，将其作为最小生成树的起始点
    // 将0这个节点的所有邻边（横切边）加入到最小生成树的候选堆中
    visit(0);
    // 然后以最小生成树的候选堆是否为空为判断依据，换句话说，如果我们的优先队列它还不为空的话，
    // 我们就继续遍历
    while (!pq.isEmpty())
    {
      // 每次我们从最小堆中取出一个最小的元素（边）
      Edge<Weight> e = pq.extractMin();

      // 因为我们是lazyPrim，所以有可能我们取出来的这个边，它根本就不是横切边，
      // 所以我们需要判断这条边它是否是一个横切边
      if (marked[e.w()] == marked[e.v()])
      {
        // 如果我们取出来的这条边它相应的两个顶点的marked标记相同的话，说明这条边的两个顶点都被访问过了
        // 那么这条边就不是一个横切边,那么我们就继续while循环，跳过这个边，不用管这个e
        continue;
      }
      else
      {
        // 否者的话，我们取出来的这条边就是一条最小生成树的边
        mst.push_back(e);
      }

      // 此时，对于e这条最小生成树的组成边来说，我们需要找到它这条边新加入区分的那个顶点，进行后续遍历
      if (!marked[e.v()])
      {
        // 如果marked[e.v()]是false，表示他就是那个蓝色点，我们就应该从这个新点开始继续下一轮的visit,把这个新点的所有横切边加入到最小堆（优先队列中来）
        visit(e.v());
      }
      else // !marked[e.w()]
      {
        // 否者的话,e.v()不是false，那么e.w()就是false，那么我们就把e.w()的横切边加入到优先队列中去
        visit(e.w());
      }
    }

    // while
    // 之后，我们就得到了最小生成树，这个时候，我们只需要对最小权值进行计算，计算完成之后，本函数功能就齐备了
    for (auto iter = mst.begin(); iter != mst.end(); ++iter)
    {
      mstWeight += (*iter).wt();
    }
  }

  ~LazyPrimMST() { delete[] marked; }

  std::vector<Edge<Weight>> mstEdges() { return mst; }

  Weight result() { return mstWeight; }
};

#endif