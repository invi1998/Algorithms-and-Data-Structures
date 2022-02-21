#include <iostream>
#include "MaxHeap.h"

int main()
{
  MaxHeap<int> mh = MaxHeap<int>(100);

  std::cout << mh.size() << std::endl;

  return 0;
}
