#ifndef UNION_FIND_TEST_HELPER_H
#define UNION_FIND_TEST_HELPER_H

#include <iostream>
#include <ctime>
#include "UnionFind.h"

namespace UnionFindTestHelper
{

  void testUF1(int n)
  {
    srand(time(NULL));
    UF1::UnionFind uf = UF1::UnionFind(n);

    time_t startTime = clock();

    // 进行n次并操作
    for (int i = 0; i < n; i++)
    {
      int a = rand() % n;
      int b = rand() % n;

      uf.unionElements(a, b);
    }
    // 进行n次查操作
    for (int i = 0; i < n; i++)
    {
      int a = rand() % n;
      int b = rand() % n;

      uf.isConnected(a, b);
    }

    time_t endTime = clock();

    std::cout << "UF1, " << 2 * n << "ops, " << double(endTime - startTime) / CLOCKS_PER_SEC << "s." << std::endl;
  }

}

#endif