#include "DenseGraph.h"
#include "Dijkstra.h"
#include "ReadGraph.h"
#include "SparseGraph.h"
#include <iostream>

using namespace std;

int main()
{

  string filename = "testG1.txt";
  int V = 5;
  // SparseGraph<int> g = SparseGraph<int>(V, true); // 创建一个节点数为5的有向图邻接表对象
  SparseGraph<int> g = SparseGraph<int>(V, false);         // 创建一个节点数为5的无向图邻接表对象
  ReadGraph<SparseGraph<int>, int> readGraph(g, filename); // 将文件filename中的图读到g对象中

  cout << "--------------------------------------------------------------------"
          "------"
       << endl;
  cout << "测试 迪杰斯拉特(Dijkstra) 算法求图的最短单源路径" << endl;
  Dijkstra<SparseGraph<int>, int> dij(g, 0); // 创建一个 dijkstra对象，传入图g和设置源点为节点0
  for (int i = 0; i < V; i++)
  {
    cout << "从源点 0 到 节点 " << i << " 的最短路径权值为："
         << dij.sortestPathTo(i) << endl;
    cout << "路径：";
    dij.showPath(i);
    cout << "......................................" << endl;
  }

  return 0;
}