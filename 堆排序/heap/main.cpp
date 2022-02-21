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

  std::cout << std::endl
            << "堆中数据从大到小排列：" << std::endl;

  // 依据最大堆的方式，一步一步的将这些堆中的元素取出来
  while (!mh.isEmpty())
  {
    std::cout << mh.extractMax() << " ";
  }

  std::cout << std::endl;

  return 0;
}
