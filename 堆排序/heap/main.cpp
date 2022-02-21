#include <iostream>
#include "MaxHeap.h"

int main()
{
  MaxHeap<int> mh = MaxHeap<int>(100);

  srand(time(NULL));

  for (int i = 0; i < 15; i++)
  {
    mh.insert(rand() % 100);
  }

  mh.testPrint();

  return 0;
}
