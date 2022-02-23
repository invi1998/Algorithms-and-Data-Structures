#ifndef __BST_H__
#define __BST_H__

#include <iostream>

// BinarySearchTree (二叉搜索树)
template <typename Key, typename Value>
class BST
{

private:
  // 这个私有的Node结构就是二叉搜索树里的节点
  struct Node
  {
    Key key;     // 查找表的 key
    Value value; // 查找表的 value
    Node *left;  // 该节点的左孩子节点
    Node *right; // 该节点的右孩子节点

    // 这个结构体的构造函数
    Node(key k, value v)
    {
      this->key = k;
      this->value = v;
      this->left = this->right = nullptr;
    }
  };

  // 对于我们这整棵树来说，他需要有一个根节点
  Node *root;
  int count; // 存储我们这棵二分搜索树有多少个节点

public:
  // 构造函数
  BST()
  {
    root = nullptr;
    count = 0;
  }

  // 析构函数
  ~BST()
  {
    // todo
  }

  // 获取节点数
  int size()
  {
    return count;
  }

  // 判空函数
  bool isEmpty()
  {
    return count == 0;
  }
};

#endif