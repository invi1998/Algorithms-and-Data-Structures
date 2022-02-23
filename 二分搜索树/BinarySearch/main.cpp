#include <iostream>
#include <vector>
#include <string>
#include "Bst.h"
#include "FileOps.h"
#include "SequenceST.h"

using namespace std;

int main()
{
  // 测试二分搜索树和顺序查找表之间的性能差距
  // 二分搜索树的性能远远优于顺序查找表

  // 使用圣经作为我们的测试用例
  string filename = "bible.txt";
  vector<string> words;

  if (FileOps::readFile(filename, words))
  {
    std::cout << "文件 \"" << filename << "\"中，"
              << "文本总词量：" << words.size() << std::endl;

    // 测试BST （二叉搜索树）
    time_t startTime = clock();

    // 统计圣经中所有词的词频
    // 注：这个词频统计方法相对简陋，没有考虑很多文本处理中的特殊问题
    // 在这里只做性能测试
    BST<string, int> bst = BST<string, int>();
    for (auto iter = words.begin(); iter != words.end(); ++iter)
    {
      int *res = bst.search(*iter);
      if (res == nullptr)
      {
        bst.insert(*iter, 1);
      }
      else
      {
        (*res)++;
      }
    }

    // 输出圣经中god一词出现的频率
    if (bst.contain("god"))
      cout << "'god' : " << *bst.search("god") << endl;
    else
      cout << "No word 'god' in " << filename << endl;

    time_t endTime = clock();

    cout << "BST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
    cout << endl;

    // 测试顺序查找表 SST
    startTime = clock();

    // 统计圣经中所有词的词频
    // 注: 这个词频统计法相对简陋, 没有考虑很多文本处理中的特殊问题
    // 在这里只做性能测试用
    SequenceST<string, int> sst = SequenceST<string, int>();
    for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++)
    {
      int *res = sst.search(*iter);
      if (res == NULL)
        sst.insert(*iter, 1);
      else
        (*res)++;
    }

    // 输出圣经中god一词出现的频率
    if (sst.contain("god"))
      cout << "'god' : " << *sst.search("god") << endl;
    else
      cout << "No word 'god' in " << filename << endl;

    endTime = clock();

    cout << "SST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
  }

  return 0;
}