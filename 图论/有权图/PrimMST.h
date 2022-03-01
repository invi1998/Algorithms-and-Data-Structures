#ifndef __PRIM_MST_H__
#define __PRIM_MST_H__

#include "Edge.h"
#include "IndexMinHeap.h"
#include <cassert>
#include <iostream>
#include <vector>

template <class Graph, class Weight>
class PrimMST
{

private:
  Graph &G;                 // 图的引用
  IndexMinHeap<Weight> ipq; // 最小索引堆, 算法辅助数据结构

  // 这里要注意，我们有一个新的容器叫做edgeTo,因为我这里最小索引堆只存储和每个节点相邻的可选横切边相应的权值，而我们使用edgeTo来存储和每一个节点相邻的那一个最短的横切边。
  // 存取一个指向这条边的Edge指针
  std::vector<Edge<Weight> *> edgeTo; // 访问的点所对应的边, 算法辅助数据结构
  bool *marked;                       // 标记数组, 在算法运行过程中标记节点i是否被访问
  std::vector<Edge<Weight>> mst;      // 存储最小生成树相应的边
  Weight mstWeight;                   // 最小生成树的权值

  void visit(int v)
  {
    // 依然是，在访问这个顶点的时候，我们要保证这个点没有被marked过
    assert(!marked[v]);
    marked[v] = true;

    typename Graph::adjIterator adj(G, v);
    for (Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next())
    {
      // 使用临边迭代器，访问顶点v的所有相邻临边

      // 找到e的相邻节点w
      int w = e->other(v);
      if (!marked[w])
      {
        // 此时e是一条横切边
        // 然后对这条横切边进行判断，我们之前是否有在edgeTo中添加过w节点相邻的横切边
        if (!edgeTo[w])
        {
          // 和w相邻的横切边没有添加过，那就把这条横切边添加进最下索引堆中。
          ipq.insert(w, e->wt());
          // 与此同时，我们的edgeTo这个数组要对w进行记录
          edgeTo[w] = e;
        }
        else if (edgeTo[w]->wt() > e->wt())
        {
          // 如果我们edgeTo中保存的那条和w相邻的横切边的权值大于我们刚刚遍历到的这条边的权值，那么就需要用我们小权值（刚刚遍历到的这条边）替换掉之前的这条边
          // 使用change方法将我们最小索引堆中的元素进行替换
          ipq.change(w, e->wt());
          edgeTo[w] = e;
        }
      }
    }
  }

public:
  PrimMST(Graph &graph) : G(graph), ipq(IndexMinHeap<double>(graph.V()))
  {
    assert(graph.E() >= 1);
    marked = new bool[G.V()];
    for (int i = 0; i < G.V(); i++)
    {
      marked[i] = false;
      edgeTo.push_back(NULL);
    }

    mst.clear();

    // prim
    visit(0);
    // 只要我们的最小索引堆还有数据（也就是还有边还需要我们继续考虑，就一直while循环）
    while (!ipq.isEmpty())
    {
      // 将此时最小的那个横切边索引取出来，做visit
      int v = ipq.extracMinIndex();
      // 这里使用断言确保索引v所应的横切边是存在的。使用edgeTo[v]就能拿到这个横切边
      assert(edgeTo[v]);
      mst.push_back(*edgeTo[v]);
      visit(v);
    }

    // 整个这个while循环就将我们的最小生成树给拿到了

    // 计算最小生成树的权值
    for (auto iter = mst.begin(); iter != mst.end(); ++iter)
    {
      mstWeight += (*iter).wt();
    }
  }

  ~PrimMST() { delete[] marked; }

  std::vector<Edge<Weight>> mstEdges() { return mst; }

  Weight result() { return mstWeight; }
};

#endif