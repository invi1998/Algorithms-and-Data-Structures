#include <iostream>
#include <iomanip>
#include "DenseGraph.h"
#include "ReadGraph.h"
#include "SparseGraph.h"

using namespace std;

int main()
{
  string filename1 = "testG1.txt";

  int V = 8;
  std::cout << fixed << setprecision(2);

  // 测试带权的稠密图
  DenseGraph<double> g1 = DenseGraph<double>(V, false);
  ReadGraph<DenseGraph<double>, double> read1(g1, filename1);
  g1.show();
  // NULL    NULL    0.26    NULL    0.38    NULL    0.58    0.16
  // NULL    NULL    0.36    0.29    NULL    0.32    NULL    0.19
  // 0.26    0.36    NULL    0.17    NULL    NULL    0.40    0.34
  // NULL    0.29    0.17    NULL    NULL    NULL    0.52    NULL
  // 0.38    NULL    NULL    NULL    NULL    0.35    0.93    0.37
  // NULL    0.32    NULL    NULL    0.35    NULL    NULL    0.28
  // 0.58    NULL    0.40    0.52    0.93    NULL    NULL    NULL
  // 0.16    0.19    0.34    NULL    0.37    0.28    NULL    NULL
  std::cout << std::endl;

  std::cout << "----------------------------------------------------------------------------------" << std::endl;
  SparseGraph<double> g2 = SparseGraph<double>(V, false);
  ReadGraph<SparseGraph<double>, double> read2(g2, filename1);
  g2.show();
  // vertex 0 :      ( to: 7, wt: 0.16 )     ( to: 4, wt: 0.38 )     ( to: 2, wt: 0.26 )     ( to: 6, wt: 0.58 )
  // vertex 1 :      ( to: 5, wt: 0.32 )     ( to: 7, wt: 0.19 )     ( to: 2, wt: 0.36 )     ( to: 3, wt: 0.29 )
  // vertex 2 :      ( to: 3, wt: 0.17 )     ( to: 0, wt: 0.26 )     ( to: 1, wt: 0.36 )     ( to: 7, wt: 0.34 )     ( to: 6, wt: 0.40 )
  // vertex 3 :      ( to: 2, wt: 0.17 )     ( to: 1, wt: 0.29 )     ( to: 6, wt: 0.52 )
  // vertex 4 :      ( to: 5, wt: 0.35 )     ( to: 7, wt: 0.37 )     ( to: 0, wt: 0.38 )     ( to: 6, wt: 0.93 )
  // vertex 5 :      ( to: 4, wt: 0.35 )     ( to: 7, wt: 0.28 )     ( to: 1, wt: 0.32 )
  // vertex 6 :      ( to: 2, wt: 0.40 )     ( to: 3, wt: 0.52 )     ( to: 0, wt: 0.58 )     ( to: 4, wt: 0.93 )
  // vertex 7 :      ( to: 4, wt: 0.37 )     ( to: 5, wt: 0.28 )     ( to: 0, wt: 0.16 )     ( to: 1, wt: 0.19 )     ( to: 2, wt: 0.34 )
  std::cout << std::endl;

  return 0;
}