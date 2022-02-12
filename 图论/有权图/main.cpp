#include <iostream>
#include <iomanip>
#include "DenseGraph.h"
#include "ReadGraph.h"

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

  return 0;
}