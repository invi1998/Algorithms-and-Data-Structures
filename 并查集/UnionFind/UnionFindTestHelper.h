#ifndef UNION_FIND_TEST_HELPER_H
#define UNION_FIND_TEST_HELPER_H

#include <iostream>
#include <ctime>
#include "UnionFind1.h"
#include "UnionFind2.h"
#include "UnionFind3.h"
#include "UnionFind4.h"
#include "UnionFind5.h"

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

  void testUF2(int n)
  {
    srand(time(NULL));
    UF2::UnionFind uf = UF2::UnionFind(n);

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

    std::cout << "UF2, " << 2 * n << "ops, " << double(endTime - startTime) / CLOCKS_PER_SEC << "s." << std::endl;
  }

  void testUF3(int n)
  {
    srand(time(NULL));
    UF3::UnionFind uf = UF3::UnionFind(n);

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

    std::cout << "UF3, " << 2 * n << "ops, " << double(endTime - startTime) / CLOCKS_PER_SEC << "s." << std::endl;
  }

  void testUF4(int n)
  {
    srand(time(NULL));
    UF4::UnionFind uf = UF4::UnionFind(n);

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

    std::cout << "UF4, " << 2 * n << "ops, " << double(endTime - startTime) / CLOCKS_PER_SEC << "s." << std::endl;
  }

  void testUF5(int n)
  {
    srand(time(NULL));
    UF5::UnionFind uf = UF5::UnionFind(n);

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

    std::cout << "UF5, " << 2 * n << "ops, " << double(endTime - startTime) / CLOCKS_PER_SEC << "s." << std::endl;
  }

}

#endif