// kruskal 算法

#ifndef __KRUSKAL_MST_H__
#define __KRUSKAL_MST_H__

#include "Edge.h"
#include "MinHeap.h"
#include "UnionFind.h"
#include <iostream>
#include <vector>

template <class Graph, class Weight>
class KruskalMST
{

private:
  std::vector<Edge<Weight>> mst;
  Weight mstWeight;

public:
  KruskalMST(Graph &graph)
  {
    // 我们实现kruskal算法第一件事情就是先对图中的所有边进行排序（这里使用堆排序）
    // 这里设置一个优先队列（最小堆），它拥有整个图的边数这么大的元素个数（空间）它里面存的每个元素是一条边
    MinHeap<Edge<Weight>> pq(graph.E());

    // 遍历一遍这张图中所有的边，
    for (int i = 0; i < graph.V(); i++)
    {
      // 使用邻边迭代器遍历节点v的所有邻边
      typename Graph::adjIterator adj(graph, i);
      for (Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next())
      {
        // 在这里有一点需要注意的是，我们的最小生成树是针对无向图来做的，而对于无向图来说，每条边其实被存了两次，一条边v[w]在G[v]中存了一次，然后又在G[w]中又被存了一次。
        // 为了避免我们在pq中也将这条边放入两次，我们需要对这个边进行一次判断。
        // 我们只去将e->V()这个值小于e->W()这样的边给放入最小堆中
        // 比如
        // 1--2这条边，它同时也是2--1这条边，但是这里我们只放入1--2这条边，而2--1就跳过不处理，就达到了我们只在优先队列中保存一条边的效果
        if (e->v() < e->w())
        {
          // 将这些边都加入到我们的优先队列pq中
          pq.insert(*e);
        }
      }
    }

    std::cout << "这里的szie大小" << pq.size() << std::endl;

    // 通过上面这个for循环，我们就将这张图中所有的边都放入了最小堆中
    // 接下里要做的就是每次将最小边拿出来，然后进行是否会形成环的比较
    // 对于这个比较的任务，这里我们就需要使用并查集了
    // 对于这个并查集，我们要开辟的空间个数，就是我们图中的顶点个数
    UnionFind uf = UnionFind(graph.V());
    // 写一个循环，在这个循环中，只要我们的最小堆它还不为空 并且
    // 最小生成树的容器里找到的边小于图中节点V-1(因为对于一个图来说，他的最小生成树的边个数是节点数-1，所以只要达到V-1，其实最小生成树就已经找到了)
    while (!pq.isEmpty() && mst.size() < graph.V() - 1)
    {
      // 从最小堆中取出一条最小边
      Edge<Weight> e = pq.extractMin();

      // 利用并查集来判断我们取出的这条边，它是否会和我们的生成树构成环
      // 判断方法就是判断e这条边它相应的两个顶点的根是否相同（如果根相同，就表示这两个节点
      // 已经连接在一起了，那么把这条边加入之后，就会构成环，反之亦反）
      if (uf.isConnected(e.v(), e.w()))
      {
        continue;
      }
      // 没有连在一起，那么就把这这两个顶点做Union操作
      uf.unionElements(e.v(), e.w());
      // 然后将这条边加入到我们的最小生成树容器中
      mst.push_back(e);
    }

    std::cout << "这里的大小" << mst.size() << std::endl;

    // 然后同样的，计算一下最小生成树的权值
    for (auto iter = mst.begin(); iter != mst.end(); ++iter)
    {
      mstWeight += (*iter).wt();
    }
  }

  ~KruskalMST() {}

  std::vector<Edge<Weight>> mstEdges() { return mst; }

  Weight result() { return mstWeight; }
};

#endif