#include <iostream>
#include "UnionFindTestHelper.h"

using namespace std;

int main()
{
  int n = 1000000;

  UnionFindTestHelper::testUF1(n);
  cout << endl;
  UnionFindTestHelper::testUF2(n);
  cout << endl;
  UnionFindTestHelper::testUF3(n);
}