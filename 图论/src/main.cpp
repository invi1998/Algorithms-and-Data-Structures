#include <iostream>
#include "DenseGraph.h"
#include "SparseGraph.h"

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

  return 0;
}